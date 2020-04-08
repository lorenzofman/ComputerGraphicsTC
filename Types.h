#pragma once

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long ulong;

typedef uchar byte;

template <typename T> using Callback = void (*)(T);
