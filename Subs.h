#ifndef SUBS_H
#define SUBS_H


char *GetTime(char Buffer[12]);
char *GetDate(char Buffer[18]);

unsigned long subchecksum(unsigned char *buf, int len);
unsigned short udpchecksum(void *buf);


#endif