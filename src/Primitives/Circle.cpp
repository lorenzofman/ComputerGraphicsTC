#include "Circle.h"
#include "Constants.h"

Circle::Circle(Float2 center, float radius)
{
	this->center = center;
	this->radius = radius;
}

bool Circle::IsPointInside(Float2 point)
{
	return Float2::DistanceSq(point, center) < radius * radius;
}

void Circle::Draw(RGBAFloat color)
{
	Canvas2D::SetColor(color);
	Canvas2D::DrawFilledCircle(center, radius, (int)(radius * 1.41f));
}

void Circle::Translate(Float2 delta)
{
	center += delta;
}
