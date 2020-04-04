#pragma once
#include "IRenderable.h"
#include "Image.h"
#include "Rect.h"
#include "Channel.h"
#include "RGBFloat.h"
class ImageHistogram : IRenderable, IKeyUpListener
{
	public:
	// Inherited via IRenderable
	virtual void Render() override;
	ImageHistogram(Scene*, InputHandler* in, Image*, Rect2D, RGBFloat, Channel ch = Channel::R);
	virtual ~ImageHistogram();
	private:
	RGBFloat color;
	Rect2D drawingArea;
	int* values;
	int max;

	// Inherited via IKeyUpListener
	virtual void OnKeyUp() override;
};

