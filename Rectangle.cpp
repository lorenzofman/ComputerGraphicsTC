#include "Rectangle.h"
Rectangle::Rectangle(Rect2D rect, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness) :
	Polygon(ExtractVerticesFromUnrotatedRect(rect), filledColor, outlineColor, outlineThickness)
{
	this->rect = rect;
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

Rect2D Rectangle::GetRect()
{
	return rect;
}

Array<Float2> Rectangle::ExtractVerticesFromUnrotatedRect(Rect2D rect)
{
	Float2* arr = new Float2[4];
	arr[3] = rect.TopLeft;
	arr[2] = rect.TopRight;
	arr[1] = rect.BottomRight;
	arr[0] = rect.BottomLeft;
	return Array<Float2>(arr, 4);
}
