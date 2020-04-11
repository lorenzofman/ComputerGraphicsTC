#include "Circle.h"
Circle::Circle(float radius, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness) :
	Shape(filledColor, outlineColor, outlineThickness)
{
	this->radius = radius;
}

void Circle::Rotate(float rad)
{
}

void Circle::Scale(float scale)
{
	radius *= scale;
}

bool Circle::IsPointInside(Float2 point)
{
	return Float2::DistanceSq(point, center) < radius * radius;
}

Rect2D Circle::GetRect()
{
	return Rect2D(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

void Circle::Draw()
{
	Canvas2D::DrawFilledCircle(center, radius, (int)radius * 2);
}