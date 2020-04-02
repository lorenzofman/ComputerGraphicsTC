#pragma once
#include "IRenderable.h"
#include "Image.h"
#include "Rect.h"
#include "Channel.h"
#include "RGBFloat.h"
class ImageHistogram : IRenderable
{
	public:
	// Inherited via IRenderable
	virtual void Render() override;
	ImageHistogram(Scene*, Image*, Rect2D, RGBFloat, Channel ch = Channel::R);
	private:
	RGBFloat color;
	Rect2D drawingArea;
	int* values;
	int max;
};

