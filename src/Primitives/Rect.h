#pragma once

#include "Array.h"
#include "Float2.h"

struct Rect2D
{
	public:

	Float2 BottomLeft;
	Float2 TopRight;
	Float2 BottomRight;
	Float2 TopLeft;
	float rotation;

	Rect2D();
	Rect2D(Float2 center, float inflate);
	Rect2D(float x1, float y1, float x2, float y2);
	Rect2D(Float2 bottomLeft, Float2 topRight);
	Rect2D(Array<Float2> points);

	void Translate(Float2 translation);
	void Rotate(float rotation);
	void Scale(float amount);
	void Scale(float x, float y);
	float LargestEdge();
	bool IsPointInside(Float2 point);
	Float2 Center();
	static Rect2D TopLeftBottomRight(Float2 topLeft, Float2 bottomRight);
	private:
	bool IsPointInsideUnRotatedRect(Float2 point);
};