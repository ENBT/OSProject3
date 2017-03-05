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
static void SExit(int status); //ADDED BY IAN BEATTY
static void SYield(); //ADDED BY IAN BEATTY
static SpaceId SExec(char* name);
extern void StartProcess(char *file), ConsoleTest(char *in, char *out);
extern void CreateProcess(int arg);
extern Thread* getThreadbyID(int id);


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
			
		

		case SC_Exec :
			{
			//printf("Inside of exec");
        	char *programName = new char[100];
        	int i = 0; 
        	int character = 1;
        	while ((i < 98) && (character != 0)) {
          		machine->ReadMem(arg1+i, 1, &character);
          		programName[i++] = (char) character;
        	}
        	programName[i] = '\0';
        	int result = SExec(programName);
        	if(result == -1){
        		printf("error with execution\n");
        		break;
        	}
        	machine->WriteRegister(2, result);
        	printf("The thing inside of Register 2 is: %d\n", machine->ReadRegister(2));

			break;
			
			}
		//BEGIN ADDED BY IAN BEATTY	
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
			//END ADDED BY IAN BEATTY	
		
		case SC_Join:
		{
			if(arg1 == -1){
				printf("This process could not be joined because it failed to execute properly.\n");
				break;
			}
			printf("Thread: %d is calling to join a process thread: %d\n", currentThread->getID(),
			 arg1);
			
			Thread * newproc = getThreadbyID(arg1);
			printf("The id for this Thread is %d\n", newproc->getID());
			newproc->parent = getThreadbyID(currentThread->getID());
			printf("The id for the parent of new proc is %d\n", newproc->parent->getID());
			currentThread->numChildren++;

			
			interrupt->SetLevel(IntOff);
			currentThread->Sleep();
			interrupt->SetLevel(IntOn);
	
			
			
			
		}	
			break;
			
		
			
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
			//ADDED BY IAN BEATTY!!!
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
		scanf("%s",buffer);

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

//ADDED BY IAN BEATTY

static void SExit(int status){
	Thread* parentToRun = NULL;
	//we will need a way to identify threads
	//if SExit can only be called if the status is 0 this check is redundant
	
	if (status == 0){
	printf("%s is calling SExit, status = %d\n\n", currentThread->getName(), status);
	if(currentThread->parent != NULL){
			printf("Thread's Parent is: %d\n", currentThread->parent->getID());
			parentToRun = currentThread->parent;
			parentToRun->numChildren--;
			if(parentToRun->numChildren == 0)
			
				scheduler->ReadyToRun(parentToRun);
		}
	currentThread->space->~AddrSpace();
	currentThread->Finish(); //should clean up everything nicely
	}
	else{
		printf("User Program: %s did not exit normally\n", currentThread->getName());
		if(currentThread->parent != NULL){
			printf("Thread's Parent is: %d\n", currentThread->parent->getID());
			parentToRun = currentThread->parent;
			parentToRun->numChildren--;
			if(parentToRun->numChildren == 0)
			
				scheduler->ReadyToRun(parentToRun);
		}
		currentThread->space->~AddrSpace();
		
		currentThread->Finish();
	}
	
	
}

//ADDED BY IAN BEATTY
static void SYield(){
	//we will need a way to identify threads
	printf("%s is calling SYield\n", currentThread->getName());
	currentThread->Yield();
	printf("%s is after the Yield\n", currentThread->getName());
}

/*
	SExec will return the number of the thread id. If the process failed to allocate memory prorperly
	or if the file does not exst, return a value of -1 signalling that this process cannot run.
	Handle disposing of process in syscall handling.
*/

static SpaceId SExec(char* name){
	
	char* filename = name;
	
	
	
	//StartProcess((char *) arg);
	
	OpenFile *executable = fileSystem->Open(filename);
    AddrSpace *space;

    if (executable == NULL) {
	printf("Unable to open file %s\n", filename);
	return -1;
    }
    space = new AddrSpace(executable);    
    if(machine->ReadRegister(2) == -1){
    	printf("Not enough Space\n");
    	delete executable;
    	return -1;
    }
    //currentThread->space = space;
    Thread *t = new Thread(filename);
    t->space = space;
    t->Fork(CreateProcess, 0);
    int id = t->getID();
    printf("The id for file, %s is: %d\n", name, id);

    delete executable;	
    
	return id;
}

static int SJoin(SpaceId id){
	








}

// end FA98

