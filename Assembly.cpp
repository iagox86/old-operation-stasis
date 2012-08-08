#include "assembly.h"

BYTE Push(REG reg)
{
	return (BYTE) (reg | PUSH);
}

BYTE Pop(REG reg)
{
	return (BYTE) (reg | POP);
}

WORD PushA()
{
	return PUSHA;
}
BYTE PushAD()
{
	return PUSHAD;
}
WORD PushF()
{
	return PUSHF;
}
WORD PopA()
{
	return POPA;
}
BYTE PopAD()
{
	return POPAD;
}
WORD PopF()
{
	return POPF;
}

WORD PushByte(BYTE value)
{
	Buffer buf;
	buf << (BYTE) PUSHBYTE;
	buf << (BYTE) value;

	return *((WORD*) buf.c_str());
}
Buffer PushDWord(DWORD value)
{
	Buffer buf;
	buf << (BYTE) PUSHDWORD;
	buf << (DWORD) value;

	return buf;
}



BYTE Ret()
{
	return RET;
}
WORD Ret(BYTE stack)
{
	Buffer buf;
	buf << RETSTACK;
	buf << stack;
	return *((WORD*) buf.c_str());
}

Buffer LongCall(DWORD offset)
{
	Buffer buf;
	buf << (BYTE) CALL;
	buf << (DWORD) offset;

	return buf;
}

Buffer LongJump(DWORD offset)
{
	Buffer buf;
	buf << (BYTE) LONGJMP;
	buf << (DWORD) offset;

	return buf;
}

Buffer ShortJump(BYTE offset)
{
	Buffer buf;
	buf << (BYTE) SHORTJMP;
	buf << (BYTE) offset;

	return buf;
}

//00401009 83 E8 04         sub         eax,4
Buffer SubtractByte(REG reg, BYTE val)
{
	Buffer buf;
	buf << (BYTE) SUB;
	buf << (BYTE) (0xE8 + reg);
	buf << (BYTE) val;

	return buf;
}


Buffer EbpToMem(DWORD addr)
{
	Buffer buf;

	buf << (BYTE) 0x89;
	buf << (BYTE) 0x2D;
	buf << (DWORD) addr;

	return buf;
}

Buffer MemToEbp(DWORD addr)
{
	Buffer buf;

	buf << (BYTE) 0x8B;
	buf << (BYTE) 0x2D;
	buf << (DWORD) addr;

	return buf;
}
