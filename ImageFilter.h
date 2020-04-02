#pragma once
#include "Image.h"
class ImageFilter
{
	public:
	virtual Image* ApplyFilter(Image* src) = 0;
};