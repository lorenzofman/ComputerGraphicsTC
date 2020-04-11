#pragma once

#include <vector>

#include "Float2.h"
#include "Shape.h"
#include "Canvas2D.h"
#include "Array.h"
#include "Rect.h"

class Polygon : Shape
{
	public:

	Polygon(Array<Float2> vertices, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness = 0);

	// Inherited via Shape
	virtual void Translate(Float2 translation) override;
	virtual void Rotate(float rad) override;
	virtual void Scale(float) override;
	virtual void Draw() override;
	virtual Rect2D GetRect() override;

	private:
	
	Array<Float2> vertices;

	static Float2 CalculateCenter(Array<Float2> vertices);
};