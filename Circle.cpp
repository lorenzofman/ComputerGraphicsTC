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

void Circle::Draw()
{
	Canvas2D::DrawFilledCircle(center, radius, (int)log2f(radius));
}
