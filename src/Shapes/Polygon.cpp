#include "Polygon.h"
Polygon::Polygon(Array<Float2> vertices, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness) : Shape(filledColor, outlineColor, outlineThickness)
{
	this->vertices = vertices;
	this->center = CalculateCenter(vertices);
	this->rect = Rect(vertices);
}

Polygon::Polygon(std::ifstream& stream) : Shape(stream)
{
	int verticesArraySize = Serial::Read<int>(stream);
	Float2* vertices = new Float2[verticesArraySize];
	for (int i = 0; i < verticesArraySize; i++)
	{
		vertices[i] = Serial::Read<Float2>(stream);
	}
	this->vertices = Array<Float2>(vertices, verticesArraySize);
	this->center = CalculateCenter(this->vertices);
	this->rect = Rect(this->vertices);
}

Polygon::~Polygon()
{
	delete[] vertices.ptr;
}

void Polygon::Serialize(std::ofstream& stream)
{
	Shape::Serialize(stream);
	Serial::Write<int>(stream, this->vertices.size);
	for (int i = 0; i < this->vertices.size; i++)
	{
		Serial::Write<Float2>(stream, this->vertices[i]);
	}
}

byte Polygon::GetShapeIdentifier()
{
	return PolygonId;
}

void Polygon::Translate(Float2 translation)
{
	for (int i = 0; i < vertices.size; i++)
	{
		vertices.ptr[i] += translation;
	}
	center += translation;
	rect.Translate(translation);
}

void Polygon::Rotate(float rad)
{
	for (int i = 0; i < vertices.size; i++)
	{
		vertices[i] -= center;
		vertices[i].Rotate(rad);
		vertices[i] += center;
	}
	rect.Rotate(rad);
}

void Polygon::Scale(float scale)
{
	for (int i = 0; i < vertices.size; i++)
	{
		vertices[i] -= center;
		vertices[i] *= scale;
		vertices[i] += center;
	}
	rect.Scale(scale);
}

void Polygon::Scale(float xScale, float yScale)
{
	for (int i = 0; i < vertices.size; i++)
	{
		vertices[i] -= center;
		vertices[i].x *= xScale;
		vertices[i].y *= yScale;
		vertices[i] += center;
	}
	rect.Scale(xScale, yScale);
}

void Polygon::Draw()
{
	Canvas2D::DrawFilledPolygon(vertices.ptr, vertices.size);
}

bool Polygon::IsPointInside(Float2 point)
{
	bool result = false;
	int j = vertices.size - 1;
	for (int i = 0; i < vertices.size; i++)
	{
		if (vertices.ptr[i].y < point.y && vertices.ptr[j].y >= point.y || vertices.ptr[j].y < point.y && vertices.ptr[i].y >= point.y)
		{
			if (vertices.ptr[i].x + (point.y - vertices.ptr[i].y) / (vertices.ptr[j].y - vertices.ptr[i].y) * (vertices.ptr[j].x - vertices.ptr[i].x) < point.x)
			{
				result = !result;
			}
		}
		j = i;
	}
	return result;
}
Rect Polygon::GetRect()
{
	return rect;
}

void Polygon::MatchRect(Rect newRect)
{
	Rect rect = GetRect();
	float oldWidth = rect.TopRight.x - rect.BottomLeft.x;
	float newWidth = newRect.TopRight.x - newRect.BottomLeft.x;

	float oldHeight = rect.TopRight.y - rect.BottomLeft.y;
	float newHeight = newRect.TopRight.y - newRect.BottomLeft.y;

	float dx = newWidth - oldWidth;
	float dy = newHeight - oldHeight;

	float ddx = newWidth / oldWidth;
	float ddy = newHeight / oldHeight;
	float max = fmaxf(ddx, ddy);

	Float2 newCenter = newRect.Center();
	Float2 oldCenter = rect.Center();
	Float2 dif = newCenter - oldCenter;

	Scale(ddx, ddy);
	Translate(dif);
	rect.rotation = newRect.rotation;
}


Float2 Polygon::CalculateCenter(Array<Float2> vertices)
{
	Rect enclosingRect = Rect(vertices);
	return enclosingRect.Center();
}
