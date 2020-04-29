#pragma once
#include <string>

#include "Canvas2D.h"
#include "../Primitives/Float2.h"
#include "../Primitives/Rect.h"
#include "../Helpers/Interpolation.h"

class Canvas2DExtensions
{
	public:
	static void DrawThickLine(Float2 start, Float2 end, RGBAFloat color, float thickness);
	static void DrawRoundedRect(Rect rect, RGBAFloat color, float roundness);
	static void DrawDashedLine(Float2 start, Float2 end, float dash = 5, float space = 2);

};
