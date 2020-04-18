#include "Circle.h"
Circle::Circle(float radius, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness) :
	Shape(filledColor, outlineColor, outlineThickness)
{
	this->radius = radius;
	this->rotation = 0;
}

void Circle::Rotate(float rad)
{
	rotation += rad;
}

void Circle::Scale(float scale)
{
	radius *= scale;
}

void Circle::Scale(float x, float y)
{
	Scale((x + y) /2);
}

bool Circle::IsPointInside(Float2 point)
{
	return Float2::DistanceSq(point, center) < radius * radius;
}

Rect2D Circle::GetRect()
{
	Rect2D rect = Rect2D(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
	rect.Translate(-center);
	rect.Rotate(rotation);
	rect.Translate(center);
	return rect;
}

void Circle::MatchRect(Rect2D rect)
{
	this->center = rect.Center();
	this->radius = rect.LargestEdge() / 2;
	//this->Rotate(rect.rotation - rotation);
}

void Circle::Draw()
{
	Canvas2D::DrawFilledCircle(center, radius, (int)radius * 2);
}