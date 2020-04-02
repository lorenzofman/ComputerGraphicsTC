#include <cmath>

#include "Rect.h"
#include "Constants.h"
Rect2D::Rect2D()
{
	BottomLeft = TopRight = Float2();
	rotation = 0;
}

Rect2D::Rect2D(float x1, float y1, float x2, float y2)
{
	BottomLeft = Float2(x1,y1);
	TopRight = Float2(x2,y2);
	rotation = 0;
}

Rect2D::Rect2D(Float2 bottomLeft, Float2 topRight)
{
	this->BottomLeft = bottomLeft;
	this->TopRight = topRight;
	rotation = 0;
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
	this->rotation += rotation;
	this->rotation = fmod(this->rotation, 2 * PI);
}

void Rect2D::Scale(double scale)
{
	BottomLeft *= (float) scale;
	TopRight *= (float) scale;
}

bool Rect2D::IsPointInside(Float2 point)
{
	Rect2D unrotatedRect = *this;
	if (rotation != 0) 
	{
		unrotatedRect.Rotate(-this->rotation); // Rollback
		point.Rotate(-this->rotation);
	}
	return unrotatedRect.IsPointInsideUnRotatedRect(point);
}

bool Rect2D::IsPointInsideUnRotatedRect(Float2 point)
{
	return(	point.x > BottomLeft.x &&
			point.y > BottomLeft.y &&
			point.x < TopRight	.x &&
			point.y < TopRight	.y);
}
