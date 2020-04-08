#pragma once

#include "Types.h"
#include "RGBAFloat.h"
#include "Float2.h"
#include "IRenderable.h"
#include "Canvas2D.h"
#include "Constants.h"

class Shape : public IRenderable
{
	public:

	Shape(RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness);

	virtual void Translate(Float2 translation);
	
	virtual void Rotate(float rad) = 0;
	
	virtual void Scale(float scale) = 0;

	virtual void Draw() = 0;

	protected:

	Float2 center;

	private: 
	
	RGBAFloat fillColor;
	
	RGBAFloat outlineColor;
	
	float outlineThickness;
	
	virtual void Render() override;

	void DrawFilled(RGBAFloat color);

	void DrawFilledOutlined(RGBAFloat fillColor, RGBAFloat borderColor, float thickness);

	void DrawOutlined(RGBAFloat color, float thickness);
};