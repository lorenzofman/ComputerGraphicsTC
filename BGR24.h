#pragma once
#include "Types.h"
#pragma pack (push, 1)

struct BGR24
{
	byte b;
	byte g;
	byte r;

	BGR24(byte, byte, byte);
};
#pragma pack (pop)