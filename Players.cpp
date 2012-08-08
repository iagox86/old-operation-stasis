#include "Players.h"

#include "Constants.h"
#include "Spoof.h"
#include "OSLog.h"

static const int STATUS = 0;
static const int RACE = 1;
static const int TEAM = 2;
static const int NAME = 3;

static const BYTE *getPlayerData(int num)
{
	return players + ((num - 1) * PLAYERSIZE);
}

static BYTE getStatus(int num)
{
	return getPlayerData(num)[STATUS];
}

static BYTE getRace(int num)
{
	return getPlayerData(num)[RACE];
}

static BYTE getTeam(int num)
{
	return getPlayerData(num)[TEAM];
}

static char *getName(int num)
{
	return (char*)(getPlayerData(num) + NAME);
}

static DWORD getMinerals(int num)
{
	return minerals[num - 1];
}

static DWORD getGas(int num)
{
	return gas[num - 1];
}


char *getNameFromNumber(int number)
{
	if(number < 1 || number > NUM_PLAYERS)
		return NULL;

	return getName(number);
}

int getNumberFromName(char *name)
{
	for(int i = 1 ; i <= NUM_PLAYERS ; i++)
		if(stricmp(name, getName(i)) == 0)
			return i;

	return -1;
}

void displayPlayers(bool loud)
{
	for(int i = 1; i <= NUM_PLAYERS; i++)
		if(getStatus(i) != NOTINGAME)
			displaySinglePlayer(i);
}

void displaySinglePlayer(int playerNum, bool loud)
{
	log("Displaying player: %d, loud = %s", playerNum, loud ? "true" : "false");
	if(playerNum < 1 || playerNum > NUM_PLAYERS)
		display("Invalid player number.");
	else
	{
		int iRace = getRace(playerNum);
		int iStatus = getStatus(playerNum);
		char *name = getName(playerNum);
		int iMinerals = getMinerals(playerNum);
		int iGas = getGas(playerNum);

		if(iRace > NUM_RACES)
			iRace = NUM_RACES;
		if(iStatus > NUM_STATUS)
			iStatus = NUM_STATUS;

		if(loud)
		{
			say(true, "\\green%d\\white: \\yellow%s \\whiteis \\yellow%s\\white, Status = \\yellow%s\\white, Resources = \\blue%u\\white/\\green%u\\white.", playerNum, name, raceList[iRace], statusList[iStatus], iMinerals, iGas);
		}
		else
		{
			display("\\green%d\\white: \\yellow%s \\whiteis \\yellow%s\\white, Status = \\yellow%s\\white, Resources = \\blue%u\\white/\\green%u\\white.", playerNum, name, raceList[iRace], statusList[iStatus], iMinerals, iGas);
		}
	}
}

void displaySinglePlayer(char *playerName, bool loud)
{
	int playerNum = getNumberFromName(playerName);
	if(playerNum == -1)
		display("\\redUnknown player.");
	else
		displaySinglePlayer(playerNum, loud);
}
