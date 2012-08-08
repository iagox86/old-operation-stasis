#include <winsock2.h>

#include "tcp.h"

int __stdcall mysend(SOCKET s, const char *buf, int len, int flags)
{
	return send(s, buf, len, flags);
}
