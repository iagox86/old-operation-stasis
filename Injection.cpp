

#include "Injection.h"

#include <malloc.h>
#include <TlHelp32.h>
#include <stdio.h>

HANDLE getProcess(const char *windowName)
{
	HANDLE pHandle = NULL;

	HWND window = FindWindow(NULL, windowName);
	
	if(window != NULL)
	{
		DWORD pid = NULL;

		GetWindowThreadProcessId(window, &pid);
		if(pid != NULL)
		{
			pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

			if(pHandle == NULL)
				printf("Unable to get process handle.\n");
		}
		else
		{
			printf("Unable to get the process id.\n");
		}
	}
	else
	{
		printf("Invalid window name.\n");
	}

	return pHandle;
}

HANDLE WINAPI InjectLibrary(const char *windowName, const char *dll)
{
	BOOL success = FALSE; //Assume that the function fails

	// Calculate the number of bytes needed fot he dll's pathname
	int pathlen = strlen(dll) + 1;

	HANDLE hProcess = getProcess(windowName);

	if(hProcess != NULL)
	{
		// Allocate space in the remote process for the pathname:
		char *remoteDll = (char *) VirtualAllocEx(hProcess, NULL, pathlen, MEM_COMMIT, PAGE_READWRITE);
		if (remoteDll != NULL)
		{
			// Copy the DLL's pathname to the remote process's address space
			if (WriteProcessMemory(hProcess, remoteDll, (PVOID) dll, pathlen, NULL))
			{
				// Get the real address of LoadLibraryW in Kernel32.dll
				PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");
				if (pfnThreadRtn != NULL)
				{
					// Create a remote thread that calls LoadLibraryW(DLLPathname)
					HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, remoteDll, 0, NULL);
					if(hThread != NULL)
					{
						// Wait for the remote thread to terminate
						WaitForSingleObject(hThread, INFINITE);
						success = TRUE;
					}
					else
					{
						printf("Unable to create remote thread.\n");
					}
				}
				else
				{
					printf("Unable to get the address of LoadLibrary.\n");
				}
			}
			else
			{
				printf("Unable to write to the remote process's memory space.\n");
			}
		}
		else
		{
			printf("Unable to allocate memory in the remote process.\n");
		}

		// Free the remote memory that continaed the DLL's pathname
		if(remoteDll != NULL)
			VirtualFreeEx(hProcess, remoteDll, 0, MEM_RELEASE);

	}
	else
	{
		printf("Unable to open the process.\n");
	}

	if(success)
		return hProcess;

	if(hProcess != NULL)
		CloseHandle(hProcess);

	return NULL;
}

BOOL WINAPI EjectLib(char *windowName, DWORD dwProcessId, PCWSTR pszLibFile)
{
	BOOL fOk = FALSE; // Assume that the function fails
	HANDLE hthSnapshot = NULL;
	HANDLE hThread = NULL;

	__try {
		// Grab a snapshot of the process
		hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
		if(hthSnapshot == NULL) __leave;

		// Get the HMODULE of the desired library
		MODULEENTRY32W me = { sizeof(me) };
		BOOL fFound = FALSE;
		BOOL fMoreMods = Module32FirstW(hthSnapshot, &me);
		for(; fMoreMods; fMoreMods = Module32NextW(hthSnapshot, &me))
		{
			fFound = (lstrcmpiW(me.szModule, pszLibFile) == 0) || (lstrcmpiW(me.szExePath, pszLibFile) == 0);
			if(fFound) break;
		}

		if(!fFound) __leave;

		// Get the real address of LoadLibraryW in Kernel32.dll
		PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
			GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "FreeLibrary");
		if (pfnThreadRtn == NULL) __leave;

		// Create a remote thread that calls LoadLibraryW(DLLPathname)
		hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, me.modBaseAddr, 0, NULL);
		if(hThread == NULL) __leave;

		// Wait for the remove thread to terminate
		WaitForSingleObject(hThread, INFINITE);

		fOk = TRUE; // Everything executed successfully
	}
	__finally
	{
		//Clean everything up
		if(hthSnapshot != NULL)
		{
			CloseHandle(hthSnapshot);
		}

	}

	return fOk;
}

