#include "CommandHandler.h"

#include "Display.h"
#include "Constants.h"
#include "Spoof.h"
#include "Players.h"
#include "Match.h"
#include "OSLog.h"
#include "Udp.h"

static const BOOL HANDLED = TRUE;

BOOL __fastcall commandWrapper(const char *message)
{
	log("Top of commandWrapper");

	if(message)
		convertColors((char*)message);

	if(message == NULL || *message != '/')
	{
		log("No message or not a command");
		return !HANDLED;
	}

	log("Attempting to process command:");
	log("Message");

	char *copy  = (char*)malloc(strlen(message) + 1);
	strcpy(copy, message);

	if(commandHandler(copy + 1) != HANDLED)
		sendPacket(SID_CHATCOMMAND, (char*)message, strlen(message) + 1);

	log("commandHandler returned successfully");

	free(copy);

	log("Completed commandWrapper");

	return TRUE;
}


BOOL __fastcall commandHandler(char *command)
{

	char *param = strchr(command, ' ');
	if(param)
		*param++ = '\0';

	log("command = %s", command);
	log("param = %s", param == NULL ? "null" : param);

	BOOL handled = !HANDLED;

	if(stricmp(command, "spoof") == 0 || stricmp(command, "s") == 0)
	{
		log("Spoofing message");
		if(param == NULL)
			display("\\redUsage: /spoof [message]");
		else
			spoofMessage(param);

		log("Spoof completed");

		handled = HANDLED;
	}
	else if(stricmp(command, "listplayers") == 0 || stricmp(command, "lp") == 0)
	{
		log("List players");
		displayPlayers(false);

		handled = HANDLED;

		log("List players completed");
	}
	else if(stricmp(command, "mp3") == 00)
	{
		log("mp3");
		char song[512];
		HWND window = FindWindow("Winamp v1.x", NULL);

		if(window != NULL)
		{
			GetWindowText(window, song, 511);

			ReplaceAll(" - Winamp", "", song);
			ReplaceAll(" - Winamp", "", song);
			ReplaceAll("[Paused]", "", song);
			ReplaceAll("[Stopped]", "", song);

			say(true, "Now playing: %s", song);
		}
		else
		{
			display("\\redCan't find winamp!");
		}

		handled = HANDLED;

		log("Completed mp3");
	}

	else if(stricmp(command, "drop") == 0)
	{
		strcpy(droppedIp, param); 
		handled = HANDLED;
	}
	else if(stricmp(command, "udp") == 0)
	{
		displayMessages = !displayMessages;
		display("displayMessages set to %d", displayMessages);
		handled = HANDLED;
	}
		

	return handled;
}