#include "Subs.h"

#include <time.h>
#include <stdio.h>

char *GetTime(char Buffer[12])
{
	// Get the time:
	long currtime = time(NULL);
	tm *Time = localtime(&currtime);
	sprintf(Buffer, "%02d.%02d.%02d", Time->tm_hour, Time->tm_min, Time->tm_sec);

	return Buffer;
}

char *GetDate(char Buffer[18])
{
	// Gets the date
	long currtime = time(NULL);
	tm *Time = localtime(&currtime);

	sprintf(Buffer, "%02d-%02d-%04d", Time->tm_mon + 1, Time->tm_mday, Time->tm_year + 1900);

	return Buffer;
}


unsigned long subchecksum(unsigned char *buf, int len)
{
	unsigned sum1=0, sum2=0;
	unsigned char *p;

	printf("len = %d\n", len);

	p = buf+len-1;
	while(len--) {
		sum2 += *p--;
		if(sum2 > 0xff)
			sum2 -= 0xff;
		sum1 += sum2;
	}
	return ((sum2 & 0xff)<<8) | ((sum1 % 0xff) & 0xff);
	//return 0x00;
}


unsigned short udpchecksum(void*buf)
{
//	dumphex((unsigned char*)buf, 0x15);
	unsigned long subsum = subchecksum((unsigned char*)buf+2, *((unsigned short*)buf+1)-2);
	unsigned long a = 0xff - ((subsum & 0xff) + (subsum >> 8)) % 0xff;
	unsigned short b = (unsigned short) (((0xff - (a + (subsum>>8)) % 0xff) & 0xff) | (a<<8));
//	plog("sum %d\n", b);
	return b;
}