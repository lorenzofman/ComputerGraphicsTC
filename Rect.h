#pragma once
#include "Float2.h"
struct Rect2D
{
	public:

	Float2 BottomLeft;
	Float2 TopRight;
	double rotation;

	Rect2D();
	Rect2D(float x1, float y1, float x2, float y2);
	Rect2D(Float2 bottomLeft, Float2 topRight);
	void Translate(Float2 translation);
	void Rotate(double rotation);
	void Scale(double amount);
	bool IsPointInside(Float2 point);

	private:
	bool IsPointInsideUnRotatedRect(Float2 point);
};