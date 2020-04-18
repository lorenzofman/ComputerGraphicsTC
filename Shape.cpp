#include "Shape.h"
Shape::Shape(RGBAFloat fillColor, RGBAFloat outlineColor, float outlineThickness)
{
	this->fillColor = fillColor;
	this->outlineColor = outlineColor;
	this->outlineThickness = outlineThickness;
	this->Translate(Float2(Screen::Width / 2, Screen::Height / 2));
}

void Shape::Translate(Float2 translation)
{
	center += translation;
}

void Shape::Render()
{
	if (outlineThickness == 0)
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

void Shape::SetMainColor(RGBAFloat color)
{
	this->fillColor = color;
}

void Shape::SetOutlineColor(RGBAFloat color)
{
	outlineColor = color;
}

Float2 Shape::GetCenter()
{
	return center;
}

float Shape::GetOutlineThickness()
{
	return outlineThickness;
}

void Shape::SetOutlineThickness(float outlineThickness)
{
	outlineThickness = std::clamp(outlineThickness, 0.0f, 1.0f);
	this->outlineThickness = outlineThickness;
}

void Shape::DrawFilled(RGBAFloat color)
{
	Canvas2D::SetColor(color);
	Draw();
}

void Shape::DrawFilledOutlined(RGBAFloat fillColor, RGBAFloat borderColor, float thickness)
{
	float ratio = 1 - thickness;
	Canvas2D::SetColor(borderColor);
	Draw();
	Scale(ratio);
	Canvas2D::SetColor(fillColor);
	Draw();
	Scale(1 / ratio); /* Rollback - might loose precision */
}

void Shape::DrawOutlined(RGBAFloat color, float thickness)
{
	DrawFilledOutlined(Colors::Background, color, thickness);
}
