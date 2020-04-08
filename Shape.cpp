#include "Shape.h"

Shape::Shape(RGBAFloat fillColor, RGBAFloat outlineColor, float outlineThickness)
{
	this->fillColor = fillColor;
	this->outlineColor = outlineColor;
	this->outlineThickness = outlineThickness;
}

void Shape::Translate(Float2 translation)
{
	center += translation;
}

void Shape::Render()
{
	if (outlineThickness > 0)
	{
		DrawFilled(fillColor);
		return;
	}

	if (fillColor.a == 0)
	{
		DrawOutlined(outlineColor, outlineThickness);
		return;
	}

	DrawFilledOutlined(fillColor, outlineColor, outlineThickness);
}

void Shape::DrawFilled(RGBAFloat color)
{
	Canvas2D::SetColor(color);
	Draw();
}

void Shape::DrawFilledOutlined(RGBAFloat fillColor, RGBAFloat borderColor, float thickness)
{
	Canvas2D::SetColor(borderColor);
	Draw();

	Scale(1 / thickness);
	Canvas2D::SetColor(fillColor);
	Draw();

	Scale(thickness); /* Rollback - might loose precision */
}

void Shape::DrawOutlined(RGBAFloat color, float thickness)
{
	DrawFilledOutlined(Background, color, thickness);
}
