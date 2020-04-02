#pragma once

#include "Image.h"
#include "Rect.h"
#include "Float2.h"
#include "Int2.h"
class Canvas2DExtensions
{
	public:
	static void DrawPoints(int h, int w, Image* image);
	static void DrawRects(int h, int w, Image* image);
	static void DrawImage(Image*);
	static Image* RasterizeImageTransformations(Image*, Scene*);
	private:
	static Rect2D MinBounds(float* xs, float* ys);
	static Rect2D CalculateContainingBoundingBox(Image* src);
	static float Min(float* arr, int size);
	static float Max(float* arr, int size);
};