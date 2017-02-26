// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
// start Ian Beatty's Code
extern int tasknumber;
// end Ian Beatty's Code

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}
// Start Ian Beatty's Code
//----------------------------------------------------------------------
// Input Identification
//	Determine a type of input.
//----------------------------------------------------------------------

void
IdentInput(int threadNum)
{
	//printf("Entering IdentInput with thread %d \n", threadNum);
	
	bool Dec = false;
	bool Int = false;
	bool Char = false;
	bool Neg = false;
	char *strP = new char();	//pointer to the first element in the char array
	printf("Waiting for input: ");
	scanf("%s", strP); 	// this doesnt work figure out how to get input correctly
	char t = strP[0]; 	// make sure t isnt \0
	int i = 0;			// counter for while loop	
	while(t != '\0')	//the logic for determining what the input is
	{
		if(t == '.' && i == 0)	//if starts with a '.' its a char array
		{
			Char = true;
			break;
		}
		if(t == '-' && i == 0)	//if starts with a '-' negative
		{
			Neg = true;
			if(strP[i+1] == '.')
			{
				Char = true;
				break;
			}
		}
		
		if(t == '.')
		{
			if(Dec == true)		//if there is already a '.' its a char array
			{
				Char = true;
				break;
			}
			
			if(strP[i+1] == '\0')	//if it ends in a '.' its a char array
			{
				Char = true;
				break;
			}
			
			Dec = true;
		}
		
		if(t >= '0' && t <= '9')
		{
			Int = true;
		}
		
		if(t != '.' && !(t >='0' && t <= '9') && !(t == '-' && i == 0))
		{
			Char = true;
			break;
		}
		i++;
		t = strP[i];
	}
	if(Char)
	{
		printf("\nCharacter String\n\n");
	}	
	else if(Neg && Dec)
	{
		printf("\nNegitive Decimal\n\n");
	}
	else if(Dec)
	{
		printf("\nDecimal\n\n");
	}
	else if(Neg && Int)
	{
		printf("\nNegitive Interger\n\n");
	}
	else if(Int)
	{
		printf("\nInterger\n\n");
	}
}

//----------------------------------------------------------------------
//Shout
//	Shout a phrase and yeild random times.
//----------------------------------------------------------------------

void
Shout(int times)
{
	
	int count = 1;
	char **array = new char*[256];
	array[0] = "violence for violence\n";
	array[1] = "is the law of beasts.\n";
	array[2] = "if that's not the rawest quote\n"; 
	array[3] = "you've ever heard\n";
	array[4] = "then get out my face.\n";
	int randPhrase = 0;
	int randYields = Random() % 4;
	randYields += 2;
	
	
	for(int i = 0; i < times; i++)
	{
		randPhrase = Random() % 5;
		printf(currentThread->getName());
		printf(" shouts: ");
		printf(array[randPhrase]);
		printf(currentThread->getName());
		printf(" has shouted %i times\n", count);
		count++;
		for(int j = 0; j < randYields; j++)
		{
			currentThread->Yield();
		}
	}
}

//----------------------------------------------------------------------
//Task2Manager
//	Start a shouting match between T threads and shout S times.
//----------------------------------------------------------------------

void
Task2Manager(int threadNum)
{
	//printf("Entering Task2Manager with thread %d \n", threadNum);
	printf("Enter number of threads (1 - 1000) : ");
	char *strPT = new char();
	int i = 0;
	int T = 0;
	scanf("%s", strPT);
	char c = strPT[0];
	while (c != '\0')
	{
		if(c > '0' && c <= '9')
		{
			//printf("Valid input!\n");
			
		}
		else if(c == '0' && i != 0)
		{
			//printf("Valid input!\n");	
		}
		else if(c == '0' && i == 0 )
		{

			printf("Invalid!!!\n");
			currentThread->Finish();
			break;	
		}
		else
		{
			printf("Invalid!!!\n");
			currentThread->Finish();
			break;
		}
		i++;
		c = strPT[i];
	}
	T = atoi(strPT);
	if(T > 1000)
	{
		printf("Input to large, setting Threads to 1000\n");
		T = 1000; //hehe T-1000 is gonna kill us all.
	}
	printf("\nEnter number of shouts (1 - 1000) : ");
	char *strPS = new char();
	i = 0;
	int S = 0;
	scanf("%s", strPS);
	char c2 = strPS[0];
	while (c2 != '\0')
	{
		if(c2 > '0' && c2 <= '9')
		{
			//printf("Valid input!\n");
			
		}
		else if(c2 == '0' && i != 0 )
		{
			//printf("Valid input!\n");
		}
		else if(c2 == '0' && i == 0 )
		{

			printf("Invalid!!!!\n");
			currentThread->Finish();
			break;	
		}
		else
		{
			printf("Invalid!!!!\n");
			currentThread->Finish();
			break;
		}
		i++;
		c2 = strPS[i];
	}
	S = atoi(strPS);
	if(S > 1000)
	{
		printf("input to large, setting Shouts to 1000\n");
		S == 1000;
	}
	for(int j = 0; j < T; j++)
	{
		char *name = new char();
		sprintf(name, "Thread %i", j);
		Thread *t = new Thread(name);
		t->Fork(Shout, S);
	}
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Entering ThreadTest");

    Thread *t = new Thread("forked thread");
	if(tasknumber == 1)
	{
		t->Fork(IdentInput, 1);
	}
	if(tasknumber == 2)
	{
		t->Fork(Task2Manager, 2);
	}
    //t->Fork(SimpleThread, 1);
	//IdentInput(0); 
	currentThread->Finish();
	//SimpleThread(0);
}
// End Ian's Code
