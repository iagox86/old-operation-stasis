#include "Spoof.h"
#include "Constants.h"
#include "OSLog.h"
#include "Match.h"


static char spoofName[MAX_MESSAGE];
static const char *spoofFile = "./spoof.txt";

void saySomethingEx(const char *Text)
{
	log("Entering saySomethingEx");
	char newStr[MAX_MESSAGE];

	
	strncpy(newStr, "\\n\\n\\n\\n\\n\\n\\n\\n\\n\\n\\n", MAX_MESSAGE);
	strncat(newStr, Text, MAX_MESSAGE);

	convertColors(newStr);

	saySomething(newStr);

	log("Leaving saySomethingEx");
}

void say(BOOL showName, const char *Text, ...)
{
	log("Entering say");
	// Displays on the screen, using printf style format
	char outStr[MAX_MESSAGE];

	va_list argptr;
	va_start(argptr, Text);
	_vsnprintf(outStr, MAX_MESSAGE, Text, argptr);

	outStr[MAX_MESSAGE - 1] = '\0';

	convertColors(outStr);

	if(showName)
		saySomething(outStr);
	else
		saySomethingEx(outStr);

	log("Leaving say");
}

void spoofMessage(const char *message)
{
	log("Entering spoofMessage");

	char command[MAX_MESSAGE];
	strcpy(command, message);

	// Make sure we actually got a command
	if(!command || !*command)
	{
		log("Parameter not found");
		display("\\redError: you must specify a parameter to spoof, eg, \"/s ~ hey\"");
		return;
	}

	char *parameter = strchr(command, ' ');
	if(parameter == NULL)
	{
		if(*spoofName == '\0')
			strcpy(spoofName, gameName);
		parameter = spoofName;
	}
	else
		*parameter++ = '\0';
	

	// I hate NOOOOOOO idea why this works, and I hate it, but we're doing it anyway.
	char p2[MAX_MESSAGE];
	strcpy(p2, parameter);

	// special commands

	// keeping setname for historic reasons
	if(stricmp(command, "name") == 0 || stricmp(command, "setname") == 0)
	{
		strcpy(spoofName, parameter);
		display("\\yellowSpoof name has been set to %s", spoofName);
	}
	else
	{
		log("Opening the file");
		FILE *spoof = fopen(spoofFile, "r");
		if(spoof == NULL)
		{
			display("\\redUnable to open spoof file: %s.", spoofFile);
		}
		else
		{

			char line[MAX_MESSAGE];
			fgets(line, MAX_MESSAGE, spoof);
			while(!feof(spoof))
			{
				if(*line != '\0' && *line != '#')
				{
					// 3 stages:
					// 1. read in till we find a word
					// 2. read in spaces/tabs
					// 3. read in till we get to the end
					char readCommand[MAX_MESSAGE];
					char readMessage[MAX_MESSAGE];

					int i;
					for(i = 0; i < MAX_MESSAGE && line[i] != ' ' && line[i] != '\t'; i++)
					{
						readCommand[i] = line[i];
					}
					readCommand[i] = '\0';

					for( ; line[i] == ' ' || line[i] == '\t'; i++)
					{
					}

					int j;
					for(j = i; j < MAX_MESSAGE && line[j] != '\n'; j++)
					{
						readMessage[j - i] = line[j];
					}
					readMessage[j - i] = '\0';


					if(stricmp(readCommand, command) == 0)
					{
						ReplaceAll("$p", p2, readMessage);
						ReplaceAll("$n", spoofName, readMessage);
						ReplaceAll("$m", gameName, readMessage);
						say(false, readMessage);
						break;
						//ReplaceAll("\\blue", "\x2", Text);
					}


				}

				fgets(line, MAX_MESSAGE, spoof);
			}

			

			log("Closing spoof file");
			fclose(spoof);
		}
	}

}
