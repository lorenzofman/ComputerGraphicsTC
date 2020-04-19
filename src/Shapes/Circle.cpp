#include "Circle.h"
Circle::Circle(float radius, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness) :
	Shape(filledColor, outlineColor, outlineThickness)
{
	this->radius = radius;
	this->rotation = 0;
}
Circle::Circle(std::ifstream& stream) : Shape(stream)
{
	this->radius = Serial::Read<float>(stream);
	this->rotation = Serial::Read<float>(stream);
}

void Circle::Serialize(std::ofstream& stream)
{
	Shape::Serialize(stream);
	Serial::Write<float>(stream, this->radius);
	Serial::Write<float>(stream, this->rotation);
}

byte Circle::GetShapeIdentifier()
{
	return CircleId;
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

Rect Circle::GetRect()
{
	Rect rect = Rect(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
	rect.Translate(-center);
	rect.Rotate(rotation);
	rect.Translate(center);
	return rect;
}

void Circle::MatchRect(Rect rect)
{
	this->center = rect.Center();
	this->radius = rect.LargestEdge() / 2;
}


void Circle::Draw()
{
	Canvas2D::DrawFilledCircle(center, radius, (int)radius * 2);
}