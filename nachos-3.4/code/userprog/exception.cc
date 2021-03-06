// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include <stdio.h>        // FA98
#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "addrspace.h"   // FA98
#include "sysdep.h"   // FA98

// begin FA98


static int SRead(int addr, int size, int id);
static void SWrite(char *buffer, int size, int id);
static void SExit(int status);
static void SYield();
static SpaceId SExec(char* name);
extern void StartProcess(char *file), ConsoleTest(char *in, char *out);
extern void CreateProcess(int arg);
extern Thread* getThreadbyID(int id);
static int SJoin(SpaceId parent);
extern Thread* threadArray[];

extern int getArrayIndex(int id);
// end FA98

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------



void
ExceptionHandler(ExceptionType which)
{
	int type = machine->ReadRegister(2);

	int arg1 = machine->ReadRegister(4);
	int arg2 = machine->ReadRegister(5);
	int arg3 = machine->ReadRegister(6);
	int Result;
	int i, j;
	char *ch = new char [500];

	switch ( which )
	{
	case NoException :
		break;
	case SyscallException :

		// for debugging, in case we are jumping into lala-land
		// Advance program counters.
		machine->registers[PrevPCReg] = machine->registers[PCReg];
		machine->registers[PCReg] = machine->registers[NextPCReg];
		machine->registers[NextPCReg] = machine->registers[NextPCReg] + 4;

		switch ( type )
		{

		case SC_Halt :
			DEBUG('t', "Shutdown, initiated by user program.\n");
			interrupt->Halt();
			break;
			
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////PROJECT 3 START//////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 		

		case SC_Exec :
			{
			//printf("Inside of exec");
        	char *programName = new char[1000];
        	int i = 0; 
        	int character = 1;
        	while ((i < 998) && (character != 0)) {
          		machine->ReadMem(arg1+i, 1, &character);
          		programName[i++] = (char) character;
        	}
        	programName[i] = '\0';
        	
        	int result = SExec(programName);
        	if(result == -1){
        		printf("error with execution\n\n");
        		machine->WriteRegister(2, result);
        		break;
        	}
        	
        	machine->WriteRegister(2, result);
			break;
			}
			
		case SC_Exit :
			//printf("In switch case type number: %d\n", type);
			//printf("arg1 = %d\n", arg1);
			if(arg1 == 0){
				//printf("in if statment arg1 = %d\n", arg1);
				
				SExit(arg1);
				
			}
			break;
			
		case SC_Yield :
			//printf("In switch case type number: %d\n", type);
			SYield();
			break;
			
		case SC_Join:
		{
			int result = 0;
			if(arg1 == -1){
				printf("This process could not be joined because it failed to execute properly.\n");
				result = -1;
				machine->WriteRegister(2, result);
				break;
			}
			printf("Thread: %d is calling to join a process thread: %d\n\n", currentThread->getID(),
			 arg1);
			 
			result = SJoin(arg1);
			machine->WriteRegister(2, result);
			break;
		}	
			break;
	
 //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////PROJECT 3 END////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 

		case SC_Read :
			if (arg2 <= 0 || arg3 < 0){
				printf("\nRead 0 byte.\n");
			}
			Result = SRead(arg1, arg2, arg3);
			machine->WriteRegister(2, Result);
			DEBUG('t',"Read %d bytes from the open file(OpenFileId is %d)",
			arg2, arg3);
			break;

		case SC_Write :
			for (j = 0; ; j++) {
				if(!machine->ReadMem((arg1+j), 1, &i))
					j=j-1;
				else{
					ch[j] = (char) i;
					if (ch[j] == '\0') 
						break;
				}
			}
			if (j == 0){
				printf("\nWrite 0 byte.\n");
				// SExit(1);
			} else {
				DEBUG('t', "\nWrite %d bytes from %s to the open file(OpenFileId is %d).", arg2, ch, arg3);
				SWrite(ch, j, arg3);
			}
			break;

			default :
			printf("Unprogrammed systemcall, type number = %d\n", type);
			//Unprogrammed system calls end up here
			break;
		}         
		break;

	case ReadOnlyException :
		puts ("ReadOnlyException");
		if (currentThread->getName() == "main")
		ASSERT(FALSE);  //Not the way of handling an exception.
		SExit(1);
		break;
	case BusErrorException :
		puts ("BusErrorException");
		if (currentThread->getName() == "main")
		ASSERT(FALSE);  //Not the way of handling an exception.
		SExit(1);
		break;
	case AddressErrorException :
		puts ("AddressErrorException");
		SExit(1);
		if (currentThread->getName() == "main")
		ASSERT(FALSE);  //Not the way of handling an exception.
		SExit(1);
		break;
	case OverflowException :
		puts ("OverflowException");
		if (currentThread->getName() == "main")
		ASSERT(FALSE);  //Not the way of handling an exception.
		SExit(1);
		break;
	case IllegalInstrException :
		puts ("IllegalInstrException");
		if (currentThread->getName() == "main")
		ASSERT(FALSE);  //Not the way of handling an exception.
		//SExit(1);
		break;
	case NumExceptionTypes :
		puts ("NumExceptionTypes");
		if (currentThread->getName() == "main")
		ASSERT(FALSE);  //Not the way of handling an exception.
		SExit(1);
		break;

		default :
		//      printf("Unexpected user mode exception %d %d\n", which, type);
		//      if (currentThread->getName() == "main")
		//      ASSERT(FALSE);
		//      SExit(1);
		break;
	}
	delete [] ch;
}


static int SRead(int addr, int size, int id)  //input 0  output 1
{
	char buffer[size+10];
	int num,Result;

	//read from keyboard, try writing your own code using console class.
	if (id == 0)
	{
		//scanf("%s",buffer);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////PROJECT 3 POSSIBLE BONUS POINTS START/////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 	
		//crossing fingers, hoping this works
  		fgets(buffer, 1000, stdin);
  		buffer[strlen(buffer) - 1] = '\0';

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////PROJECT 3 POSSIBLE BONUS POINTS END///////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 	

		num=strlen(buffer);
		if(num>(size+1)) {

			buffer[size+1] = '\0';
			Result = size+1;
		}
		else {
			buffer[num+1]='\0';
			Result = num + 1;
		}

		for (num=0; num<Result; num++)
		{  machine->WriteMem((addr+num), 1, (int) buffer[num]);
			if (buffer[num] == '\0')
			break; }
		return num;

	}
	//read from a unix file, later you need change to nachos file system.
	else
	{
		for(num=0;num<size;num++){
			Read(id,&buffer[num],1);
			machine->WriteMem((addr+num), 1, (int) buffer[num]);
			if(buffer[num]=='\0') break;
		}
		return num;
	}
}



static void SWrite(char *buffer, int size, int id)
{
	//write to terminal, try writting your own code using console class.
	if (id == 1)
	printf("%s", buffer);
	//write to a unix file, later you need change to nachos file system.
	if (id >= 2)
	WriteFile(id,buffer,size);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////PROJECT 3 START//////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 

static void SExit(int status){
	
	
	//we will need a way to identify threads
	//if SExit can only be called if the status is 0 this check is redundant
	/*
	if(index != -1 && index < 32)
			{
				interrupt->SetLevel(IntOff);
				threadArray[index] = NULL;
				interrupt->SetLevel(IntOn);
				
			}
	*/
	machine->WriteRegister(2, status);
	if (status == 0){
	printf("User Program: %s exited normally\n\n", currentThread->getName());
	
	currentThread->space->~AddrSpace();
	currentThread->Finish(); //should clean up everything nicely
	}
	else{
		printf("User Program: %s did not exit normally\n\n", currentThread->getName());
		
		currentThread->space->~AddrSpace();
		
		currentThread->Finish();
	}	
}

static void SYield(){
	//we will need a way to identify threads
	printf("%s is Yielding\n\n", currentThread->getName());
	currentThread->Yield();
}

/*
	SExec will return the number of the thread id. If the process failed to allocate memory prorperly
	or if the file does not exst, return a value of -1 signalling that this process cannot run.
	Handle disposing of process in syscall handling.
*/

static SpaceId SExec(char* name){
	
	char* filename = name;
	
	OpenFile *executable = fileSystem->Open(filename);
    AddrSpace *space;

    if (executable == NULL) {
	printf("Unable to open file %s\n", filename);
	return -1;
    }
    interrupt->SetLevel(IntOff);
    space = new AddrSpace(executable);    
    
    if(machine->ReadRegister(2) == -1){
    	delete executable;
    	return -1;
    }
    //currentThread->space = space;
    Thread *t = new Thread(filename);
    t->space = space;
    t->Fork(CreateProcess, 0);
    int id = t->getID();
    printf("Allocated space for Process :%d\n",id);
   

    delete executable;	
    interrupt->SetLevel(IntOn);
    
	return id;
}

static int SJoin(SpaceId me){
	interrupt->SetLevel(IntOff);
	Thread * newproc = getThreadbyID(me);
	if(newproc != NULL){
		
		newproc->parent = getThreadbyID(currentThread->getID());
		currentThread->Sleep();
		
		currentThread->numChildren++;
		return 1;
			}
		

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////PROJECT 3 END////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 


