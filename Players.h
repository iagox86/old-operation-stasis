// Players.h
// by iago
// Sept. 10/2003
//
// These are functions for displaying the characters and such

#ifndef PLAYERS_H
#define PLAYERS_H

#include "Display.h"
#include "Constants.h"
#include "Spoof.h"


enum Races
{
	ZERG = 0,
	TERRAN = 1,
	PROTOSS = 2,
	NUM_RACES = 3
};

static const char *raceList[] = { "zerg", "terran", "protoss", "unknown" };

enum Status
{
	NOTINGAME = 0,
	COMPUTER = 1,
	HUMAN = 2,
	DEAD = 0x0B,
	NUM_STATUS = 0x0C
};

static const char *statusList[] = { "not in game", "computer", "human", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "dead", "unknown" };
				   
				   
char *getNameFromNumber(int number);
int getNumberFromName(char *name);
void displayPlayers(bool loud = false);
void displaySinglePlayer(int playerNum, bool loud = false);
void displaySinglePlayer(char *playerName, bool loud = false);


#endif