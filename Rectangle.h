#pragma once

#include "Polygon.h"
#include "Rect.h"
#include "Array.h"
#include "RGBAFloat.h"
#include "Float2.h"
class Rectangle : public Polygon
{
	public:
	Rectangle(Rect2D, RGBAFloat filledColor, RGBAFloat outlineColor = RGBAFloat::Blank, float outlineThickness = 0);

	// Inherited via Polygon
	virtual bool IsPointInside(Float2) override;
	virtual void Rotate(float) override;
	virtual void Scale(float) override;
	virtual void Scale(float, float) override;
	virtual void Translate(Float2) override;
	virtual Rect2D GetRect() override;

	private:
	static Array<Float2> ExtractVerticesFromUnrotatedRect(Rect2D);
	Rect2D rect;
};