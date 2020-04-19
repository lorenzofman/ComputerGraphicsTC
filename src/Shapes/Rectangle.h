#pragma once

#include <iostream>
#include <fstream>

#include "../Shapes/Polygon.h"
#include "../DataStructures/Array.h"
#include "../Primitives/Rect.h"
#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Float2.h"
class Rectangle : public Polygon
{
	public:
	Rectangle(Rect2D, RGBAFloat filledColor, RGBAFloat outlineColor = RGBAFloat::Blank, float outlineThickness = 0);
	
	Rectangle(std::ifstream&);

	virtual void Serialize(std::ofstream&) override;
	virtual byte GetShapeIdentifier() override;
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