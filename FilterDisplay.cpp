#include "FilterDisplay.h"

#include "Display.h"
#include "OSLog.h"

void __stdcall filter(char *str)
{
	log("entering filter");
	for(size_t i = 0; i < strlen(str); i++)
		if(str[i] < 0x20)
			str[i] = '#';
	log("leaving filter: %s", str);
}

void __fastcall filterDisplay()
{
	__asm
	{
		test esi, esi
		jz skip

		cmp dl, SHOW_COLORS
		je skip

		push esi
		call filter

skip:

	}
}