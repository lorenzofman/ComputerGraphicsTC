#pragma once
#include <vector>
#include <iostream>
#include <fstream>

#include "../Primitives/Float2.h"
#include "Shape.h"
#include "../Canvas2D/Canvas2D.h"
#include "../DataStructures/Array.h"
#include "../Primitives/Rect.h"
#include "../Primitives/Types.h"

class Polygon : public Shape
{
	public:

	Polygon(Array<Float2> vertices, RGBAFloat filledColor, RGBAFloat outlineColor = Colors::Blank, float outlineThickness = 0);
	
	Polygon(std::ifstream& stream);

	~Polygon();

	virtual void Serialize(std::ofstream&) override;
	virtual byte GetShapeIdentifier() override;
	// Inherited via Shape
	virtual void Translate(Float2 translation) override;
	virtual void Rotate(float rad) override;
	virtual void Scale(float) override;
	virtual void Scale(float, float) override;
	virtual void Draw() override;
	virtual bool IsPointInside(Float2) override;
	virtual Rect GetRect() override;
	virtual void MatchRect(Rect) override;
	
	private:

	Array<Float2> vertices;
	Rect rect;

	static Float2 CalculateCenter(Array<Float2> vertices);
};