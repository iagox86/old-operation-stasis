#include "Display.h"
#include "Constants.h"
#include "Match.h"
#include "Players.h"
#include "OSLog.h"

#include <stdio.h>
#include <stdarg.h>


void __stdcall display(const char *text, ...)
{
	char *outStr = (char*) malloc(MAX_MESSAGE);

	va_list argptr;
	va_start(argptr, text);
	_vsnprintf(outStr, MAX_MESSAGE, text, argptr);

	convertColors(outStr);
	displayBuffer(outStr, SHOW_COLORS, 15000 + GetTickCount(), 0);

	free(outStr);
}

char * __fastcall convertColors(char *Text)
{
	log("convertColors");
	ReplaceAll("\\blue", "\x2", Text);
	ReplaceAll("\\yellow", "\x3", Text);
	ReplaceAll("\\white", "\x4", Text);
	ReplaceAll("\\grey", "\x5", Text);
	ReplaceAll("\\gray", "\x5", Text);
	ReplaceAll("\\red", "\x6", Text);
	ReplaceAll("\\green", "\x7", Text);
	ReplaceAll("\\n", "\xA", Text);
	ReplaceAll("\\boom", "\xC", Text);
	ReplaceAll("\\right", "\x12", Text);
	ReplaceAll("\\center", "\x13", Text);

	ReplaceAll("#1", getNameFromNumber(1), Text);
	ReplaceAll("#2", getNameFromNumber(2), Text);
	ReplaceAll("#3", getNameFromNumber(3), Text);
	ReplaceAll("#4", getNameFromNumber(4), Text);
	ReplaceAll("#5", getNameFromNumber(5), Text);
	ReplaceAll("#6", getNameFromNumber(6), Text);
	ReplaceAll("#7", getNameFromNumber(7), Text);
	ReplaceAll("#8", getNameFromNumber(8), Text);

	log("Completed convertColors");

	return Text;
}

/*char * __fastcall killColors(char *Text)
{
	ReplaceAll("\x2", "\\blue", Text);
	ReplaceAll("\x3", "\\yellow", Text);
	ReplaceAll("\x4", "\\white", Text);
	ReplaceAll("\x5", "\\grey", Text);
	ReplaceAll("\x6", "\\red", Text);
	ReplaceAll("\x7", "\\green", Text);
	ReplaceAll("\xA", "\\n", Text);
	ReplaceAll("\xC", "\\boom", Text);
	ReplaceAll("\x12", "\\right", Text);
	ReplaceAll("\x13", "\\center", Text);

	return Text;
}*/
