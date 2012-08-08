// Display.h
// Created Sept 9/2003
// by Ron
//
// This is a file for faking 0x0F incoming packets

#ifndef DISPLAY_H
#define DISPLAY_H

#define SHOW_COLORS 0x10

#include "Display.h"

#include "Constants.h"

void __stdcall display(const char *text, ...);

char * __fastcall convertColors(char *Text);
//char * __fastcall killColors(char *Text);




#endif