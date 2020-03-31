#pragma once

#include "Types.h"
#include "IRenderable.h"
#include "ColorSpace.h"
#include "Float2.h"
struct Image : IRenderable
{
	byte* data;
	uint bytesSize;
	ColorSpace colorSpace;
	int width;
	int height;
	Float2 position;
	double scale;
	double rotation;

	Image(byte* data, uint bytesSize, ColorSpace colorSpace, int width, int height, Scene *scene);

	~Image();

	void Render();

};