#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <windows.h>
#include "Buffer.h"

#define POP			(BYTE) 0x58
#define PUSH		(BYTE) 0x50

typedef enum _REG
{
	EAX	= (BYTE) 0x00,
	ECX = (BYTE) 0x01,
	EDX = (BYTE) 0x02,
	EBX = (BYTE) 0x03,
	ESP = (BYTE) 0x04,
	EBP = (BYTE) 0x05,
	ESI = (BYTE) 0x06,
	EDI = (BYTE) 0x07
} REG;

#define NOP			(BYTE) 0x90
#define RET			(BYTE) 0xC3
#define RETSTACK    (BYTE) 0xC4
#define CALL		(BYTE) 0xE8
#define LONGJMP		(BYTE) 0xE9
#define SHORTJMP	(BYTE) 0xEB

#define PUSHA		(WORD) 0x6066
#define PUSHAD		(WORD) 0x60
#define POPA		(WORD) 0x6166
#define POPAD		(WORD) 0x61
#define PUSHF		(WORD) 0x9C66
#define POPF		(WORD) 0x9D66

#define PUSHBYTE    (BYTE) 0x6A
#define PUSHDWORD   (BYTE) 0x68

#define SUB         (BYTE) 0x83

// simulates mov reg, dword ptr [esp+distance]; 
// returns 4 bytes of machine code
DWORD ReadStack(REG reg, BYTE distance);
// Reverse of ReadStack
// simulates mov dword ptr [esp+distance], reg
DWORD WriteStack(REG reg, BYTE distance);

// Push or Pop a register
BYTE Push(REG reg);
BYTE Pop(REG reg);
BYTE PushAD();
WORD PushA();
WORD PushF();
BYTE PopAD();
WORD PopA();
WORD PopF();
WORD PushByte(BYTE value);
Buffer PushDWord(DWORD value);



BYTE Ret();
WORD Ret(BYTE stack);

Buffer LongCall(DWORD offset);
Buffer LongJump(DWORD offset);
Buffer ShortJump(BYTE offset);

// sub reg, val
Buffer SubtractByte(REG reg, BYTE val);
Buffer EbpToMem(DWORD addr);
Buffer MemToEbp(DWORD addr);


#endif