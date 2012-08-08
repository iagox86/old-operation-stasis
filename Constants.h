// Constants.h
// by Ron
// 7/31/03
//
// This is simply a file of battle.net constants

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <windows.h>

static const char *windowName = "Brood War";

#define MAX_MESSAGE 512

static const int displayAddress = 0x004699B0;

static const SOCKET *TCPSocket  = (SOCKET*)0x1902F2B8;

// Typedefs for important functions
typedef bool (__fastcall *FCTalk)		(const char*);
typedef bool (__fastcall *FCSendTCP)	(DWORD packetCode, char *packetData, DWORD length);
typedef bool (__fastcall *FCDisplay)    (const char* message, int color, int stopTime, int unknown);

static const FCTalk saySomething				= (FCTalk)    0x00470AC0;
static const FCSendTCP sendPacket				= (FCSendTCP) 0x19016A10;
static const FCDisplay displayBuffer			= (FCDisplay) 0x004699B0;
// int __fastcall DisplayOnScreen(char *message,int color,int unk2,int timeToStop)

// Pointers to catchers and lengths



// Player stuff
static const int NUM_PLAYERS = 8;
static const BYTE* players = (BYTE*) 0x64F1C0;
static const int PLAYERSIZE = 36;

static const DWORD *minerals = (DWORD *) 0x004FD4A0;
static const DWORD *gas =      (DWORD *) 0x004FD4D0;


static char *SS_FORMAT = (char *) 0x004E29E8;

static const char *gameName =		(char*)		0x19035310;
static const char *channelName =	(char*)		0x19033F20;


//-----------------
// Everything after this is old stuff


// Pointers to various useful functions
//static const FCString SendChannelText			   = (FCString) 0x1901A610;
//static const FCStringInt SCDisplay				   = (FCStringInt) 0x19017EE0;   

// Pointers to places to patch
static void *STACK_ADDR							   = (void*) 0x004438F0;


static void *CHANNEL_CATCHER					   = (void*) 0x19008340;
static DWORD CHANNEL_CATCHER_LENGTH				   = (DWORD) 0x190083DE - (DWORD)CHANNEL_CATCHER;                                                    

static void *TCP_OUT_CATCHER					   = (void*) 0x19015a63;
static DWORD TCP_OUT_CATCHER_LENGTH				   = (DWORD) 5;		

static void *TCP_IN_CATCHER						   = (void*) 0x19017383;
static DWORD TCP_IN_CATCHER_LENGTH				   = (DWORD) 7;

static void *RECVFROM_CATCHER					   = (void*) 0x19014192;                                                               
static DWORD RECVFROM_CATCHER_LENGTH			   = (DWORD) 6;

static void *SPENDGAS_CATCHER					   = (void*) 0x004022DC;
static DWORD SPENDGAS_CATCHER_LENGTH               = 7;






// Thanks to KP for codes! ;-;
const DWORD SID_NULL                               = 0x00;
const DWORD SID_0x0001                             = 0x01;
const DWORD SID_STOPADV                            = 0x02;
const DWORD SID_0x0003                             = 0x03;
const DWORD SID_SERVERLIST                         = 0x04;
const DWORD SID_CLIENTID                           = 0x05;
const DWORD SID_STARTVERSIONING                    = 0x06;
const DWORD SID_REPORTVERSION                      = 0x07;
const DWORD SID_0x0008                             = 0x08;
const DWORD SID_GETADVLISTEX                       = 0x09;
const DWORD SID_ENTERCHAT                          = 0x0a;
const DWORD SID_GETCHANNELLIST                     = 0x0b;
const DWORD SID_JOINCHANNEL                        = 0x0c;
const DWORD SID_0x000D                             = 0x0d;
const DWORD SID_CHATCOMMAND                        = 0x0e;
const DWORD SID_CHATEVENT                          = 0x0f;
const DWORD SID_LEAVECHAT                          = 0x10;
const DWORD SID_0x0011                             = 0x11;
const DWORD SID_LOCALEINFO                         = 0x12;
const DWORD SID_FLOODDETECTED                      = 0x13;
const DWORD SID_UDPPINGRESPONSE                    = 0x14;
const DWORD SID_CHECKAD                            = 0x15;
const DWORD SID_CLICKAD                            = 0x16;
const DWORD SID_QUERYMEM                           = 0x17;
const DWORD SID_0x0018                             = 0x18;
const DWORD SID_MESSAGEBOX                         = 0x19;
const DWORD SID_STARTADVEX2                        = 0x1a;
const DWORD SID_GAMEDATAADDRESS                    = 0x1b;
const DWORD SID_STARTADVEX3                        = 0x1c;
const DWORD SID_LOGONCHALLENGEEX                   = 0x1d;
const DWORD SID_CLIENTID2                          = 0x1e;
const DWORD SID_0x001F                             = 0x1f;
const DWORD SID_BROADCAST                          = 0x20;
const DWORD SID_DISPLAYAD                          = 0x21;
const DWORD SID_NOTIFYJOIN                         = 0x22;
const DWORD SID_SETCOOKIE                          = 0x23;
const DWORD SID_GETCOOKIE                          = 0x24;
const DWORD SID_PING                               = 0x25;
const DWORD SID_READUSERDATA                       = 0x26;
const DWORD SID_WRITEUSERDATA                      = 0x27;
const DWORD SID_LOGONCHALLENGE                     = 0x28;
const DWORD SID_LOGONRESPONSE                      = 0x29;
const DWORD SID_CREATEACCOUNT                      = 0x2a;
const DWORD SID_SYSTEMINFO                         = 0x2b;
const DWORD SID_GAMERESULT                         = 0x2c;
const DWORD SID_GETICONDATA                        = 0x2d;
const DWORD SID_GETLADDERDATA                      = 0x2e;
const DWORD SID_FINDLADDERUSER                     = 0x2f;
const DWORD SID_CDKEY                              = 0x30;
const DWORD SID_CHANGEPASSWORD                     = 0x31;
const DWORD SID_0x0032                             = 0x32;
const DWORD SID_GETFILETIME                        = 0x33;
const DWORD SID_0x0034                             = 0x34;
const DWORD SID_0x0035                             = 0x35;
const DWORD SID_CDKEY2                             = 0x36;
const DWORD SID_0x0037                             = 0x37;
const DWORD SID_0x0038                             = 0x38;
const DWORD SID_0x0039                             = 0x39;
const DWORD SID_0x003A                             = 0x3a;
const DWORD SID_0x003B                             = 0x3b;
const DWORD SID_CHECKDATAFILE2                     = 0x3c;
const DWORD SID_CREATEACCOUNT2                     = 0x3d;
const DWORD SID_0x003E                             = 0x3e;
const DWORD SID_STARTVERSIONING2                   = 0x3f;
const DWORD SID_0x0040                             = 0x40;
const DWORD SID_QUERYADURL                         = 0x41;
const DWORD SID_CDKEY3                             = 0x42;
const DWORD SID_0x0043                             = 0x43;
const DWORD SID_0x0044                             = 0x44;
const DWORD SID_0x0045                             = 0x45;
const DWORD SID_0x0046                             = 0x46;
const DWORD SID_0x0047                             = 0x47;
const DWORD SID_0x0048                             = 0x48;
const DWORD SID_0x0049                             = 0x49;
const DWORD SID_0x004A                             = 0x4a;
const DWORD SID_0x004B                             = 0x4b;
const DWORD SID_0x004C                             = 0x4c;
const DWORD SID_0x004D                             = 0x4d;
const DWORD SID_0x004E                             = 0x4e;
const DWORD SID_0x004F                             = 0x4f;
const DWORD SID_AUTH_INFO                          = 0x50;
const DWORD SID_AUTH_CHECK                         = 0x51;
const DWORD SID_AUTH_ACCOUNTCREATE                 = 0x52;
const DWORD SID_AUTH_ACCOUNTLOGON                  = 0x53;
const DWORD SID_AUTH_ACCOUNTLOGONPROOF             = 0x54;
const DWORD SID_AUTH_ACCOUNTCHANGE                 = 0x55;
const DWORD SID_AUTH_ACCOUNTCHANGEPROOF            = 0x56;
const DWORD SID_AUTH_ACCOUNTUPGRADE                = 0x57;
const DWORD SID_AUTH_ACCOUNTUPGRADEPROOF           = 0x58;
const DWORD SID_AUTH_RECONNECT                     = 0x59;
const DWORD SID_AUTH_RECONNECTPROOF                = 0x5a;
const DWORD SID_AUTH_DISCONNECT                    = 0x5b;



// The following are dwId's for 0x0F packets:
const DWORD ID_USERINCHANNEL            = 0x01;
const DWORD ID_USERJOINCHANNEL          = 0x02;
const DWORD ID_USERLEAVECHANNEL         = 0x03;
const DWORD ID_WHISPERFROM              = 0x04;
const DWORD ID_INCOMING_CHAT            = 0x05;
const DWORD ID_ERROR                    = 0x06;
const DWORD ID_CHANNELJOIN              = 0x07;
const DWORD ID_CHANGEFLAGS              = 0x09;
const DWORD ID_WHISPERTO                = 0x0A;
const DWORD ID_INFORMATION              = 0x12;
const DWORD ID_CHANNELFULL              = 0x13;
const DWORD ID_IGNOREON                 = 0x15;
const DWORD ID_IGNOREOFF                = 0x16;
const DWORD ID_EMOTE                    = 0x17;

// Flags
const DWORD OPERATOR_FLAG               = 0x02;
const DWORD SPEAKER_FLAG                = 0x04;
const DWORD SYSTEMADMIN_FLAG            = 0x08;
const DWORD CHAT_FLAG                   = 0x10;
const DWORD SQUELCHED_FLAG              = 0x20;
const DWORD SPECTATOR_FLAG              = 0x40;

// Colors in channel
const DWORD CHANNEL_GREY                = 0x11;
const DWORD CHANNEL_GREEN               = 0x12;
const DWORD CHANNEL_YELLOW              = 0x13;
const DWORD CHANNEL_CYAN                = 0x14;
const DWORD CHANNEL_WHITE               = 0x10;
const DWORD CHANNEL_RED                 = 0x19;

// Colors in-game
const DWORD COLOR_NORMAL                = 0x01;
const DWORD COLOR_BLUE                  = 0x02;
const DWORD COLOR_YELLOW                = 0x03;
const DWORD COLOR_WHITE                 = 0x04;
const DWORD COLOR_GREY                  = 0x05;
const DWORD COLOR_RED                   = 0x06;
const DWORD COLOR_GREEN                 = 0x07;
const DWORD COLOR_LINEFEED              = 0x0A;
const DWORD COLOR_BOOM                  = 0x0C;

//Also alignments
const DWORD ALIGN_LEFT                  = 0x11;
const DWORD ALIGN_RIGHT                 = 0x12;
const DWORD ALIGN_CENTER                = 0x13;

#endif