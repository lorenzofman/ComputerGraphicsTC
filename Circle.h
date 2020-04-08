#pragma once

#include "Float2.h"
#include "Shape.h"
#include "Canvas2D.h"
#include "Constants.h"

class Circle : public Shape
{
	public:

	Circle(float radius, RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness = 0);

	// Inherited via Shape
	virtual void Rotate(float rad) override;
	virtual void Scale(float scale) override;
	virtual void Draw() override;

	private:

	float radius;
};

