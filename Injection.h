#ifndef INJECTION_H
#define INJECTION_H

#include <windows.h>

HANDLE WINAPI InjectLibrary(const char *windowName, const char *dll);
BOOL WINAPI EjectLib(HANDLE hProcess, DWORD dwProcessId, PCWSTR pszLibFile);



#endif