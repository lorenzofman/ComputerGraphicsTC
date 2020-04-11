#include "Polygon.h"
Polygon::Polygon(Array<Float2> vertices, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness) : Shape(filledColor, outlineColor, outlineThickness)
{
	this->vertices = vertices;
	this->center = CalculateCenter(vertices);
}

void Polygon::Translate(Float2 translation)
{
	for (int i = 0; i < vertices.size; i++)
	{
		vertices.ptr[i] += translation;
	}
	center += translation;
}

void Polygon::Rotate(float rad)
{
	for (int i = 0; i < vertices.size; i++)
	{
		vertices[i] -= center;
		vertices[i].Rotate(rad);
		vertices[i] += center;
	}
}

void Polygon::Scale(float scale)
{
	for (int i = 0; i < vertices.size; i++)
	{
		vertices[i] -= center;
		vertices[i] *= scale;
		vertices[i] += center;
	}
}

void Polygon::Draw()
{
	Canvas2D::DrawFilledPolygon(vertices.ptr, vertices.size);
}

bool Polygon::IsPointInside(Float2)
{
	return false; // Todo: implement
}
Rect2D Polygon::GetRect()
{
	return Rect2D(vertices);
}

Float2 Polygon::CalculateCenter(Array<Float2> vertices)
{
	Rect2D enclosingRect = Rect2D(vertices);
	return enclosingRect.Center();
}
