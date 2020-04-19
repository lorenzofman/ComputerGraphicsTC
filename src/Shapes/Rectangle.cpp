#include "Rectangle.h"
Rectangle::Rectangle(Rect rect, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness) :
	Polygon(ExtractVerticesFromUnrotatedRect(rect), filledColor, outlineColor, outlineThickness)
{
	this->rect = rect;
}

Rectangle::Rectangle(std::ifstream& stream) : Polygon(stream)
{
	this->rect = Serial::Read<Rect>(stream);
}

void Rectangle::Serialize(std::ofstream& stream)
{
	Polygon::Serialize(stream);
	Serial::Write(stream, this->rect);
}

byte Rectangle::GetShapeIdentifier()
{
	return RectangleId;
}

bool Rectangle::IsPointInside(Float2 point)
{
	return rect.IsPointInside(point);
}

void Rectangle::Rotate(float rad)
{
	Polygon::Rotate(rad);
	rect.Translate(-center);
	rect.Rotate(rad);
	rect.Translate(center);
}

void Rectangle::Scale(float scale)
{
	Polygon::Scale(scale);
	rect.Translate(-center);
	rect.Scale(scale);
	rect.Translate(center);
}

void Rectangle::Scale(float x, float y)
{
	Polygon::Scale(x, y);
	rect.Translate(-center);
	rect.Scale(x, y);
	rect.Translate(center);
}

void Rectangle::Translate(Float2 translation)
{
	Polygon::Translate(translation);
	rect.Translate(translation);
}

Rect Rectangle::GetRect()
{
	return rect;
}

Array<Float2> Rectangle::ExtractVerticesFromUnrotatedRect(Rect rect)
{
	Float2* arr = new Float2[4];
	arr[3] = rect.TopLeft;
	arr[2] = rect.TopRight;
	arr[1] = rect.BottomRight;
	arr[0] = rect.BottomLeft;
	return Array<Float2>(arr, 4);
}
