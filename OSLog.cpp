#include "oslog.h"

#include <stdio.h>

#include "Subs.h"
#include "Constants.h"

static const char *filename = "./OSLog.txt";
static const int filterPriority = 5;


void __cdecl log(const char *text, ...)
{
	char *outStr = (char*) malloc(MAX_MESSAGE);

	va_list argptr;
	va_start(argptr, text);
	_vsnprintf(outStr, MAX_MESSAGE, text, argptr);

	FILE *file = fopen(filename, "a");
	if(file != NULL)
	{
		char date[18];
		char time[12];
		fprintf(file, "%s %s >>> %s\n", GetDate(date), GetTime(time), outStr);
	}
	else
	{
		// There's nothing we can here..
	}
	fclose(file);

	free(outStr);
}