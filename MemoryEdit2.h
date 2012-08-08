// MemoryEdit.h
// by iago
// Created 7/28/2003
//
// This is a class that will allow a user to easily edit a process's memory and restore it 
// when the program ends
//


#ifndef MEMORYEDIT2_H
#define MEMORYEDIT2_H

#include <windows.h>
#include <assert.h>
#include <windows.h>
#include <iostream>
#include <string>
#include "Buffer.h"

// This struct holds the data that can restore exactly 1 patch
// I've decided to make it a really simple list structure so it can hold as many as I need
typedef struct _Restore
{
	void *original;  // Pointer to the original data (PatchLength bytes)
	void *patchLocation; // Pointer to where the patch was applied
	DWORD length; // The number of bytes that were patched
	void *wrapper; // The generated wrapper
	DWORD ebpBackup;
	DWORD returnAddress;

	struct _Restore *next;
} Restore;

class MemoryEdit2
{
private:
	Restore *restoreHead;
	
public:

	MemoryEdit2();
	~MemoryEdit2();
	
	// BytesToOverwrite must be at least 5 and has to be an exact number of machine code commands,
	// overwriting part of a command will cause problems.  Also, don't overwrite a jump or call that
	// goes outside of the overwritten text (or any offset-operator that goes outside of the patch)
	// because it will cause a problem :)
	// Also, patching over a push will cause problems.. you'll get over it :P
	bool PatchMem(const void *sourceCode, const void *destinationFunction, const DWORD size, const bool generateWrapper, const bool preserveRegisters, const bool preserveFlags);
};

#endif