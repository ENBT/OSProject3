// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -N -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "noff.h"
#include "bitmap.h"
#ifdef HOST_SPARC
#include <strings.h>
#endif


//Initialize and Declare the bitmap object. This stores a map of the amount of available pages and will control what program is allowed to run.
// >>Check bitmap.cc for further understanding
BitMap *map = new BitMap(NumPhysPages);
//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void
SwapHeader(NoffHeader *noffH)
{
	noffH->noffMagic = WordToHost(noffH->noffMagic);
	noffH->code.size = WordToHost(noffH->code.size);
	noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
	noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
	noffH->initData.size = WordToHost(noffH->initData.size);
	noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
	noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
	noffH->uninitData.size = WordToHost(noffH->uninitData.size);
	noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
	noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an adress space to run a user program.
//	Load the program from a file "executable", and set everything
//	up so that we can start executing user instructions.
//
//	Assumes that the object code file is in NOFF format.
//
//	First, set up the translation from program memory to physical 
//	memory.  For now, this is really simple (1:1), since we are
//	only uniprogramming, and we have a single unsegmented page table
//
//	"executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------



AddrSpace::AddrSpace(OpenFile *executable)
{
	NoffHeader noffH;
	unsigned int i, size;
	

	executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
	if ((noffH.noffMagic != NOFFMAGIC) &&
		(WordToHost(noffH.noffMagic) == NOFFMAGIC))
		SwapHeader(&noffH);
	ASSERT(noffH.noffMagic == NOFFMAGIC);

	// how big is address space?
	size = noffH.code.size + noffH.initData.size + noffH.uninitData.size
		+ UserStackSize;	// we need to increase the size
							// to leave room for the stack
	numPages = divRoundUp(size, PageSize);
	
	size = numPages * PageSize;
	
	//Check if the number of pages this program takes is bigger than the amount of physical pages Available.
	if(numPages > map->NumClear())
	{
		printf("Sorry bud, not enough memory. Nothing Personal.\n");
		//Write -1 into the second register for confirmation and return to caller.
		machine->WriteRegister(2, -1);
		return;
	}

	ASSERT(numPages <= NumPhysPages);		// check we're not trying
											// to run anything too big --
											// at least until we have
											// virtual memory
											

	DEBUG('a', "Initializing address space, num pages %d, size %d\n",
		numPages, size);
	printf("Initializing address space, num pages %d, size %d, Physical Pages Available %d\n",
		numPages, size, map->NumClear()); 
	// first, set up the translation
	
	
	

	//print out the status of the current map. Prints out the pages that are "marked" in the bitmap
	//Marked pages are those that have taken up space for user programs.
	map->Print();
	
	//>>Previously written code
	pageTable = new TranslationEntry[numPages];
	for (i = 0; i < numPages; i++) {
		pageTable[i].virtualPage = i;	// for now, virtual page # = phys page #
		pageTable[i].physicalPage = map->Find(); //Finds the first available page and marks it for a reference in the page table
		pageTable[i].valid = TRUE;
		pageTable[i].use = FALSE;
		pageTable[i].dirty = FALSE;
		pageTable[i].readOnly = FALSE;  // if the code segment was entirely on 
										// a separate page, we could set its 
										// pages to be read-only

		bzero(&machine->mainMemory[pageTable[i].physicalPage * PageSize], PageSize);
	}
	map->Print();//Print out marked pages after process has allocated
	

	// zero out the entire address space, to zero the unitialized data segment 
	// and the stack segment
	// bzero(machine->mainMemory, size);

	// then, copy in the code and data segments into memory
	if (noffH.code.size > 0) {
		DEBUG('a', "Initializing code segment, at 0x%x, size %d\n",
			noffH.code.virtualAddr, noffH.code.size);
		executable->ReadAt(&(machine->mainMemory[ChangeMe(noffH.code.virtualAddr)]),
			noffH.code.size, noffH.code.inFileAddr);
	}
	if (noffH.initData.size > 0) {
		DEBUG('a', "Initializing data segment, at 0x%x, size %d\n",
			noffH.initData.virtualAddr, noffH.initData.size);
		executable->ReadAt(&(machine->mainMemory[ChangeMe(noffH.initData.virtualAddr)]),
			noffH.initData.size, noffH.initData.inFileAddr);
	}

}


//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
// 	Dealloate an address space.  Unmarks all the pages that this page
//	table takes up in the bitmap. delete the page table afterwards.
// 	Function afterwards deletes the thread that was running this process
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
	unsigned int z, pnum;
	z = 0;
	pnum = numPages;
	
	if(pageTable[0].physicalPage > z)
	{
	
		z = pageTable[0].physicalPage;
		pnum  = numPages + z;
	}
	else
		z = 0; 
		
	for(; z < pnum; z++){
		map->Clear(z);
		printf("Deleting Page: %d\n",z);
		}
			
	
	delete pageTable;
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
	int i;

	for (i = 0; i < NumTotalRegs; i++)
		machine->WriteRegister(i, 0);

	// Initial program counter -- must be location of "Start"
	machine->WriteRegister(PCReg, 0);

	// Need to also tell MIPS where next instruction is, because
	// of branch delay possibility
	machine->WriteRegister(NextPCReg, 4);

	// Set the stack register to the end of the address space, where we
	// allocated the stack; but subtract off a bit, to make sure we don't
	// accidentally reference off the end!
	machine->WriteRegister(StackReg, numPages * PageSize - 16);
	DEBUG('a', "Initializing stack register to %d\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//	For now, nothing!
//----------------------------------------------------------------------

void AddrSpace::SaveState()
{}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState()
{
	machine->pageTable = pageTable;
	machine->pageTableSize = numPages;
}
//Changes Virtual Address into Physical Address
int AddrSpace::ChangeMe(int vaddr)
{
	//Algorithm to translate virtual page into a physical page.
	int physaddr = pageTable[vaddr / PageSize].physicalPage * PageSize + (vaddr % PageSize);
	return physaddr;

}

