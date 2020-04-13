#pragma once

#include "Float2.h"
#include "Shape.h"
#include "Rect.h"
#include "Canvas2D.h"
#include "Constants.h"

class Circle : public Shape
{
	public:

	Circle(float radius, RGBAFloat filledColor, RGBAFloat outlineColor = RGBAFloat(0, 0, 0), float outlineThickness = 0);

	// Inherited via Shape
	virtual void Rotate(float rad) override;
	virtual void Scale(float scale) override;
	virtual void ScaleHorizontally(float xScale) override;
	virtual void ScaleVertically(float yScale) override;

	virtual bool IsPointInside(Float2) override;
	virtual Rect2D GetRect() override;
	protected:

	// Inherited via Shape
	virtual void Draw() override;

	private:

	float radius;
};
