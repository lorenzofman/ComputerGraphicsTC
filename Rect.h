#pragma once
#include "Float2.h"
struct Rect2D
{
	Float2 BottomLeft;
	Float2 TopRight;
	double rotation;

	public:

	Rect2D();
	Rect2D(Float2 bottomLeft, Float2 topRight);
	void Translate(Float2 translation);
	void Rotate(double rotation);
	void Scale(float amount);
	bool IsPointInside(Float2 point);

	private:
	bool IsPointInsideUnRotatedRect(Float2 point);
};