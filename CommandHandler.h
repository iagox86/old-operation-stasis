#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <windows.h>

BOOL __fastcall commandWrapper(const char *message);
BOOL __fastcall commandHandler(char *command);

#endif