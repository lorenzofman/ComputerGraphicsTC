#include "Rect.h"

Rect2D::Rect2D(Float2 bottomLeft, Float2 topRight)
{
	this->BottomLeft = bottomLeft;
	this->TopRight = topRight;
}

void Rect2D::Translate(Float2 translation)
{
	BottomLeft += translation;
	TopRight += translation;
}

void Rect2D::Rotate(double rotation)
{
	BottomLeft.Rotate(rotation);
	TopRight.Rotate(rotation);
}

void Rect2D::Scale(float scale)
{
	BottomLeft *= scale;
	TopRight *= scale;
}
