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

Rect2D::Rect2D(Array<Float2> points)
{
	float x1, x2, y1, y2;
	x1 = x2 = points.ptr[0].x;
	y1 = y2 = points.ptr[0].y;

	for (int i = 1; i < points.size; i++)
	{
		if (points.ptr[i].x < x1)
		{
			x1 = points.ptr[i].x;
		}
		else if (points.ptr[i].x > x2)
		{
			x2 = points.ptr[i].x;
		}
		if (points.ptr[i].y < y1)
		{
			y1 = points.ptr[i].y;
		}
		else if (points.ptr[i].y > y2)
		{
			y2 = points.ptr[i].y;
		}
	}
	BottomLeft = Float2(x1, y1);
	TopRight = Float2(x2, y2);
	rotation = 0;
}

void Rect2D::Translate(Float2 translation)
{
	BottomLeft += translation;
	TopRight += translation;
}

void Rect2D::Rotate(float rotation)
{
	BottomLeft.Rotate(rotation);
	TopRight.Rotate(rotation);
	this->rotation += rotation;
	this->rotation = fmodf(this->rotation, 2 * PI);
}

void Rect2D::Scale(float scale)
{
	BottomLeft *= scale;
	TopRight *= scale;
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

Float2 Rect2D::Center()
{
	return Float2(BottomLeft.x + TopRight.x, BottomLeft.y + TopRight.y) * 0.5f;
}

Float2 Rect2D::BottomRight()
{
	return Float2(TopRight.x, BottomLeft.y);
}

Float2 Rect2D::TopLeft()
{
	return Float2(BottomLeft.x, TopRight.y);
}

bool Rect2D::IsPointInsideUnRotatedRect(Float2 point)
{
	return(	point.x > BottomLeft.x &&
			point.y > BottomLeft.y &&
			point.x < TopRight	.x &&
			point.y < TopRight	.y);
}
