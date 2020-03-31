#pragma once
#include "Float2.h"
struct Rect2D
{
	Float2 BottomLeft;
	Float2 TopRight;

	Rect2D(Float2 bottomLeft, Float2 topRight);

	void Translate(Float2 translation);
	void Rotate(double rotation);
	void Scale(float amount);
};