#pragma once
#include "Canvas2D.h"
#include "Float2.h"
#include "Rect.h"
class Canvas2DExtensions
{
	public:
	static void DrawThickLine(Float2 start, Float2 end, RGBAFloat color, float thickness);
	static void DrawRoundedRect(Rect2D rect, RGBAFloat color, float roundness);
};
