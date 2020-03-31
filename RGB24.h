#pragma once
#include "Types.h"
#pragma pack (push, 1)

struct RGB24
{
	byte r;
	byte g;
	byte b;

	RGB24(byte, byte, byte);
};
#pragma pack (pop)