//
// This will work for Starcraft 1.11b

#include "MemoryEdit2.h"
#include "Constants.h"
#include "CommandHandler.h"
#include "Display.h"
#include "EnhancedFunctions.h"
#include "FilterDisplay.h"
#include "OSLog.h"
#include "Udp.h"
#include "Tcp.h"
#include "OSLog.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>



MemoryEdit2 * me;

//void __declspec(naked) __fastcall patchSnp()

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{

			me = new MemoryEdit2();

			if(me->PatchMem((void*) 0x00470AC8, commandWrapper, 5, false, false, false) == false)
			{
				display("\\redError patching memory to catch commands.");
				log("Error patching memory to catch commands.");
			}

			if(me->PatchMem((void*) 0x0043ECB8, getScreenshotFile, 5, false, false, false) == false)
			{
				display("\\redError patching memory for enhanced screenshot files.");
				log("Error patching for screenshot files");
			}

			if(me->PatchMem((void*) 0x004699B4, filterDisplay, 6, true, true, true) == false)
			{
				display("\\redError patching memory to filter incoming chat.");
				log("Error patching memory to filter incoming chat.");
			}

			
			log("Dll successfully injected");
		}


		break;

	case DLL_PROCESS_DETACH:

		{

			delete me;

			log("Dll successfully removed");

			break;
		}
	}

    return TRUE;
}
