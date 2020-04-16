#pragma once

#include "Types.h"
#include "RGBAFloat.h"
#include "Float2.h"
#include "IRenderable.h"
#include "Canvas2D.h"
#include "Constants.h"
#include "Screen.h"
#include "Rect.h"

class Shape : public IRenderable
{
	public:

	Shape(RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness);

	virtual void Translate(Float2 translation);

	virtual void Rotate(float rad) = 0;

	virtual void Scale(float scale) = 0;

	virtual void Scale(float x, float y) = 0;

	virtual void Render() override;

	virtual bool IsPointInside(Float2) = 0;

	virtual Rect2D GetRect() = 0;

	Float2 GetCenter();

	protected:

	Float2 center;

	virtual void Draw() = 0;

	private:

	RGBAFloat fillColor;

	RGBAFloat outlineColor;

	float outlineThickness;

	void DrawFilled(RGBAFloat color);

	void DrawFilledOutlined(RGBAFloat fillColor, RGBAFloat borderColor, float thickness);

	void DrawOutlined(RGBAFloat color, float thickness);

};