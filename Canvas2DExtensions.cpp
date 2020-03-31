#include <iostream>
#include <cmath>

#include "Canvas2DExtensions.h"
#include "Canvas2D.h"
#include "RGB24.h"
#include "RGBFloat.h"
#include "ColorConversions.h"
#include "Rect.h"

BGR24* ReinterpretByteBufferAsBGRBuffer(byte* arr)
{
	return (BGR24*)arr;
}

Rect2D ApplyTransformations(int x, int y, Image* image)
{
	x -= image->width / 2;
	y -= image->height / 2;
	float fx = (float)x;
	float fy = (float)y;
	Rect2D pixel = Rect2D(Float2(fx, fy), Float2(fx + 1, fy + 1));
	pixel.Rotate(image->rotation);
	pixel.Scale((float) image->scale);
	pixel.Translate(image->position);
	return pixel;
}

//https://www.quora.com/Given-two-diagonally-opposite-points-of-a-square-how-can-I-find-out-the-other-two-points-in-terms-of-the-coordinates-of-the-known-points
void DrawPixel(Rect2D px)
{
	float* xs = new float[4];
	float* ys = new float[4];

	float x1 = px.BottomLeft.x;
	float y1 = px.BottomLeft.y;

	float x3 = px.TopRight.x;
	float y3 = px.TopRight.y;

	float x2 = (x1 + x3 + y1 - y3) / 2;
	float y2 = (x3 - x1 + y1 + y3) / 2;

	float x4 = (x1 + x3 + y3 - y1) / 2;
	float y4 = (x1 - x3 + y1 + y3) / 2;

	xs[0] = x1;
	xs[1] = x2;
	xs[2] = x3;
	xs[3] = x4;

	ys[0] = y1;
	ys[1] = y2;
	ys[2] = y3;
	ys[3] = y4;

	Canvas2D::DrawFilledPolygon(xs, ys, 4);

	delete[] xs;
	delete[] ys;
}

void Canvas2DExtensions::DrawImage(Image* image)
{
	int w = image->width;
	int h = image->height;
	BGR24* color = ReinterpretByteBufferAsBGRBuffer(image->data);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			auto rgb = ColorConversions::BGR24ToRGB24(color[idx]);
			Rect2D pixelPos = ApplyTransformations(x, y, image);
			RGBFloat fColor = ColorConversions::RGB24ToRGBFloat(rgb);
			Canvas2D::SetColor(fColor.r, fColor.g, fColor.b);
			DrawPixel(pixelPos);
		}
	}
}