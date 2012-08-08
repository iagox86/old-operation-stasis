#include "EnhancedFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <direct.h>

#include "Display.h"
#include "Subs.h"
#include "OSLog.h"


int __fastcall getScreenshotFile(char *str, size_t size, int whocares, int unk)
{
	log("getScreenshotFile entered");
	mkdir("ss");

	char date[18];
	GetDate(date);
	sprintf(str, "ss\\%s", GetDate(date));
	mkdir(str);
	
	
	char time[12];
	sprintf(str, "ss\\%s\\%s.bmp", date, GetTime(time));

	log("creating screenshot -- %s", str);

	return TRUE;
}

