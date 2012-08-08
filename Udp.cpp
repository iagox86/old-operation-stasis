#include <winsock2.h>


#include "udp.h"

#include "display.h"
#include "buffer.h"
#include "subs.h"

static SOCKET udpSocket;

BOOL displayMessages;
char droppedIp[20];




struct Message {  
 unsigned long udptype;  // 0
 unsigned short checksum;  // 4
 unsigned short len; // 6
 unsigned short pos1; // 8
 unsigned short pos2; // 10
 unsigned char cls; // 12
 unsigned char cmd; // 13
 unsigned char sender; // 14
 unsigned char resend; // 15
 char data[100]; // 16+
 }; 

char view[20] = "";

void __stdcall processUdp(int playerNum, SOCKET s, BYTE *data, int len, sockaddr *to)
{
	/*	
	//display("len = %d", msg.len);
	
	//if(len > 30)
	{
		//Buffer buf;
		//buf._AddToBuffer((const BYTE*) data, len);
		//display(buf.toString().c_str() );
		if(to != NULL)
		{
			sockaddr_in *tempSocket = (sockaddr_in*) to;
			char ip[20];
			strncpy(ip, inet_ntoa(tempSocket->sin_addr), 19);

			if(view[0] == '\0')
			{
				strcpy(view, ip);
				display("cls = %02X, cmd = %02X, sender = %02X, resend = %02X", data[12], data[13], data[14], data[15]);
			}
			else if(stricmp(view, ip) == 0)
			{
				display("cls = %02X, cmd = %02X, sender = %02X, resend = %02X", data[12], data[13], data[14], data[15]);
			}

//			if(displayMessages)
//				display("\\greySending packet to %s (len = %d)", ip, len);
			
		}
	}*/
}

void __fastcall mysendto()
{
	__asm
	{
		push edx
		push esi
		push eax
		push ecx
		push ebx
		call processUdp
	}
}