#include "MemoryEdit2.h"
#include "Assembly.h"


MemoryEdit2::MemoryEdit2()
{
	restoreHead = NULL;
}

MemoryEdit2::~MemoryEdit2()
{
	Restore *restoreData = restoreHead;

	while(restoreData)
	{
		WriteProcessMemory(GetCurrentProcess(), restoreData->patchLocation, restoreData->original, restoreData->length, NULL);
		free(restoreData->original);
		Restore *next = restoreData->next;
		free(restoreData);
		free(restoreData->wrapper);
		restoreData = next;
	}
}

// Note -- recursion will break this
// because it only mallocs memory once
bool MemoryEdit2::PatchMem(const void *sourceCode, const void *destinationFunction, const DWORD size, const bool generateWrapper, const bool preserveRegisters, const bool preserveFlags)
{
	assert(size >= 5);

	bool passed = false;

	// Set up our restoration data
	Restore *restoreData = (Restore*) malloc(sizeof(Restore));
	restoreData->next = restoreHead;
	restoreData->patchLocation = (void*) sourceCode;
	restoreData->length = size;
	restoreHead = restoreData;

	restoreData->original = malloc(size);

	// Read the original data
	if(ReadProcessMemory(GetCurrentProcess(), sourceCode, restoreData->original, size, NULL))
	{
		// This is going to be stored in memory and ran before my code is called
		Buffer wrapper;
		restoreData->wrapper = malloc(0x50 + size);

		// **Store ebp in some allocated memory
		// Allocate room to back up ebp
		wrapper << EbpToMem((DWORD)&restoreData->ebpBackup);
		// **Pop return address into Ebp
		wrapper << Pop(EBP);
		// **Move Ebp into some allocated memory
		wrapper << EbpToMem((DWORD)&restoreData->returnAddress);
		// **Restore original Ebp
		wrapper << MemToEbp((DWORD)&restoreData->ebpBackup);
		// **Do the overwritten code
		if(generateWrapper)
			for(DWORD i = 0; i < size; i++)
				wrapper << ((BYTE*) restoreData->original)[i];
		// **Back up ebp, just in case it changed
		wrapper << EbpToMem((DWORD)&restoreData->ebpBackup);
		// **Push registers
		if(preserveRegisters)
			wrapper << PushAD();
		// **Push flags
		if(preserveFlags)
			wrapper << PushF();
		// **Call the function
		int currentPosition = wrapper.GetSize();

		wrapper << (LongCall((DWORD) destinationFunction - ((DWORD) restoreData->wrapper + currentPosition) - LongCall(0).GetSize()));
		// **Pop flags
		if(preserveFlags)
			wrapper << PopF();
		// **Pop registers
		if(preserveRegisters)
			wrapper << PopAD();
		// **Move the return address back into Ebp
		wrapper << MemToEbp((DWORD)&restoreData->returnAddress);
		// **Push Ebp
		wrapper << Push(EBP);
		// **Move the original value of Ebp back
		wrapper << MemToEbp((DWORD)&restoreData->ebpBackup);
		// **Return
		wrapper << Ret();

		memcpy(restoreData->wrapper, wrapper.c_str(), wrapper.GetSize());;



		// The wrapper is complete, now we generate the patch
		Buffer patch;
		patch << LongCall((DWORD)restoreData->wrapper - (DWORD)sourceCode - LongCall(0).GetSize());
		
		while(patch.GetSize() < size)
			patch << NOP;

		WriteProcessMemory(GetCurrentProcess(), (void*)sourceCode, patch.c_str(), patch.GetSize(), NULL);


		passed = true;
	}

	return passed;
}


