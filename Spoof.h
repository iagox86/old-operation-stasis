// Spoof.h
// by iago
// Created Sept. 10/2003
//
// This is for spoofing messages

#ifndef SPOOF_H
#define SPOOF_H

#include "Display.h"
#include <iostream>
#include <strstream>

using namespace std;

// This will spoof a message based on Message
void spoofMessage(const char *Message);
void say(BOOL showName, const char *Text, ...);

#endif