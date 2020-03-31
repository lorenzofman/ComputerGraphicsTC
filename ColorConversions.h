#pragma once
#include "RGB24.h"
#include "BGR24.h"
#include "RGBFloat.h"
class ColorConversions
{
	public:
	static RGB24 RGBFloatToRGB24(RGBFloat);
	static BGR24 RGB24ToBGR24(RGB24);
	static RGB24 BGR24ToRGB24(BGR24);
	static RGBFloat RGB24ToRGBFloat(RGB24);
};

