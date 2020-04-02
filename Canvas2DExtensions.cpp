#include <iostream>
#include <cmath>
#include <algorithm>

#include "Canvas2DExtensions.h"
#include "Canvas2D.h"
#include "RGBFloat.h"

Rect2D ApplyTransformations(int x, int y, Image* image)
{
	x -= image->width / 2;
	y -= image->height / 2;
	float fx = (float)x;
	float fy = (float)y;
	Rect2D pixel = Rect2D(Float2(fx, fy), Float2(fx + 1, fy + 1));
	pixel.Rotate(image->GetRotation());
	pixel.Scale((float)image->GetScale());
	pixel.Translate(image->GetPosition());
	return pixel;
}

Rect2D ApplyRotationAndScale(int x, int y, Image* image)
{
	float fx = (float)x;
	float fy = (float)y;
	Rect2D pixel = Rect2D(Float2(fx, fy), Float2(fx + 1, fy + 1));
	pixel.Rotate(image->GetRotation());
	pixel.Scale((float)image->GetScale());
	return pixel;
}


//https://www.quora.com/Given-two-diagonally-opposite-points-of-a-square-how-can-I-find-out-the-other-two-points-in-terms-of-the-coordinates-of-the-known-points
/* Calculate points and packs them in array with all x values followed by all y values*/
float* CalculatePoints(Rect2D px)
{
	float* xs = new float[8];

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

	xs[4] = y1;
	xs[5] = y2;
	xs[6] = y3;
	xs[7] = y4;

	return xs;
}

void DrawPixel(Rect2D px)
{
	float* xys = CalculatePoints(px);
	float* xs = &xys[0];
	float* ys = &xys[4];
	Canvas2D::DrawFilledPolygon(xs, ys, 4);

	delete[] xys;
}

void Canvas2DExtensions::DrawPoints(int h, int w, Image* image)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			RGBFloat fColor = image->pixels[idx];
			Canvas2D::SetColor(fColor.r, fColor.g, fColor.b);
			Canvas2D::DrawPoint(x + (int)image->GetPosition().x - image->width / 2, y + (int) image->GetPosition().y - image->height / 2);
		}
	}
}

void Canvas2DExtensions::DrawRects(int h, int w, Image* image)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			RGBFloat fColor = image->pixels[idx];
			Rect2D pixelPos = ApplyTransformations(x, y, image);
			Canvas2D::SetColor(fColor.r, fColor.g, fColor.b);
			DrawPixel(pixelPos);
		}
	}
}

void Canvas2DExtensions::DrawImage(Image* image)
{
	int w = image->width;
	int h = image->height;
	if (image->GetScale() == 1 && image->GetRotation() == 0)
	{
		DrawPoints(h, w, image);
	}
	else
	{
		DrawRects(h, w, image);
	}
}

float Canvas2DExtensions::Min(float* arr, int size)
{
	float min = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}

float Canvas2DExtensions::Max(float* arr, int size)
{
	float max = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

Rect2D Canvas2DExtensions::MinBounds(float* xs, float* ys)
{
	return Rect2D(Min(xs, 4), Min(ys, 4), Max(xs, 4), Max(ys, 4));
}

Rect2D Canvas2DExtensions::CalculateContainingBoundingBox(Image* src)
{
	Rect2D baseRect = Rect2D(0, 0, (float) src->width, (float) src->height);
	Rect2D transformedRect = baseRect;

	transformedRect.Rotate(src->GetRotation());
	transformedRect.Scale((float)src->GetScale());

	float* xys = CalculatePoints(transformedRect);

	float* xs = &xys[0];
	float* ys = &xys[4];

	Rect2D rect = MinBounds(xs, ys);
	delete[] xys;
	return rect;
}

void Bresenham(std::vector<Int2>& points, int x1, int y1, int x2, int y2)
{
	bool yIsSteep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (yIsSteep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = (float) (x2 - x1);
	const float dy = (float) fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x <= maxX; x++)
	{
		points.push_back((yIsSteep) ? Int2(y, x) : Int2(x, y));

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void ScanLine(std::vector<Int2>& points, int yMin, int yMax)
{
	int height = (yMax - yMin) + 1; // inclusive
	int* min = new int[height];
	int* max = new int[height];
	for (int i = 0; i < height; i++)
	{
		min[i] = INT_MAX;
		max[i] = INT_MIN;
	}
	for (auto point : points)
	{
		if (point.x < min[point.y - yMin])
		{
			min[point.y - yMin] = point.x;
		}
		if (point.x > max[point.y - yMin])
		{
			max[point.y - yMin] = point.x;
		}
	}
	for (int i = 0; i < height; i++)
	{
		if (min[i] == INT_MAX)
		{
			continue;
		}
		for (int j = min[i] + 1; j < max[i]; j++)
		{
			points.push_back(Int2(j, i + yMin));
		}
	}
	delete[] min, max;
}

std::vector<Int2> RasterizeTriangle(const Int2& a, const Int2& b, const Int2& c, const Rect2D& bounds)
{
	std::vector<Int2> points = std::vector<Int2>();

	Bresenham(points, a.x, a.y, b.x, b.y); // AB
	Bresenham(points, a.x, a.y, c.x, c.y); // AC
	Bresenham(points, b.x, b.y, c.x, c.y); // BC

	int minY = std::min(std::min(a.y, b.y), c.y);
	int maxY = std::max(std::max(a.y, b.y), c.y);

	ScanLine(points, minY, maxY);

	return points;
}

void PaintBuffer(RGBFloat* buffer, RGBFloat color, int w, int h, const std::vector<Int2>& points)
{
	int size = w * h;
	for (auto&& point : points)
	{
		if (point.y < 0 || point.y >= h || point.x < 0 || point.x >= w)
		{
			continue;
		}
		int idx = point.y * w + point.x;
		if (idx >= 0 && idx < size) 
		{
			buffer[idx] = color;
		}
	}
}

void RasterizeRect(RGBFloat* buffer, Rect2D px, Rect2D rect, RGBFloat color)
{
	float* xys = CalculatePoints(px);
	Float2 a = Float2(xys[0], xys[4]);
	Float2 b = Float2(xys[1], xys[5]);
	Float2 c = Float2(xys[2], xys[6]);
	Float2 d = Float2(xys[3], xys[7]);
	auto abc = RasterizeTriangle(a, b, c, rect);
	auto abd = RasterizeTriangle(a, d, c, rect);
	int w = (int)(rect.TopRight.x - rect.BottomLeft.x);
	int h = (int)(rect.TopRight.y - rect.BottomLeft.y);
	PaintBuffer(buffer, color, w, h, abc);
	PaintBuffer(buffer, color, w, h, abd);
	delete[] xys;
}

/* Create new image with applied translation, rotation, scale */
Image* Canvas2DExtensions::RasterizeImageTransformations(Image* src, Scene* sc)
{
	Rect2D rect = CalculateContainingBoundingBox(src);
	Int2 topRight = Int2((int)ceilf(rect.TopRight.x), (int)ceilf(rect.TopRight.y));
	Int2 bottomLeft = Int2((int)ceilf(rect.BottomLeft.x), (int)ceilf(rect.BottomLeft.y));
	int w = topRight.x - bottomLeft.x;
	int h = topRight.x - bottomLeft.x;
	int size = w * h;
	RGBFloat* pixels = new RGBFloat[size];
	memset(pixels, 0, size * sizeof(RGBFloat));
	for (int y = 0; y < src->width; y++)
	{
		for (int x = 0; x < src->height; x++)
		{
			int idx = y * src->width + x;
			Rect2D px = ApplyRotationAndScale(x, y, src);
			printf("Drawing rect -> (%f, %f, %f, %f)", px.BottomLeft.x, px.BottomLeft.y, px.TopRight.x, px.TopRight.y);
			std::cout << std::endl;
			RasterizeRect(pixels, px, rect, src->pixels[idx]);
		}
	}
	Image* dst = new Image(pixels, w, h, sc, src->input);
	dst->SetPosition(src->GetPosition());
	return dst;
}