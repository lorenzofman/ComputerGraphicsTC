#pragma once
#include <vector>

#include "Float2.h"
#include "Shape.h"
#include "Canvas2D.h"
#include "Array.h"
#include "Rect.h"
class Polygon : public Shape
{
	public:

	Polygon(Array<Float2> vertices, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness = 0);

	// Inherited via Shape
	virtual void Translate(Float2 translation) override;
	virtual void Rotate(float rad) override;
	virtual void Scale(float) override;
	virtual void Draw() override;
	virtual bool IsPointInside(Float2) override;
	virtual Rect2D GetRect() override;

	private:

	Array<Float2> vertices;

	static Float2 CalculateCenter(Array<Float2> vertices);
};