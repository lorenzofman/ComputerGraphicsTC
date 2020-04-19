#pragma once

#include <algorithm>

#include "../Primitives/Types.h"
#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Float2.h"
#include "../Primitives/Rect.h"
#include "../Primitives/Constants.h"
#include "../World/Screen.h"
#include "../Canvas2D/Canvas2D.h"
#include "../Serialization/Serial.h"
#include "../Interfaces/IRenderable.h"
class Shape : public IRenderable
{
	public:

	Shape(RGBAFloat filledColor, RGBAFloat outlineColor, float outlineThickness);

	Shape(std::ifstream& stream);
	virtual void Serialize(std::ofstream&);

	virtual byte GetShapeIdentifier() = 0;

	virtual void Translate(Float2 translation);

	virtual void Rotate(float rad) = 0;

	virtual void Scale(float scale) = 0;

	virtual void Scale(float x, float y) = 0;

	virtual void Render() override;

	virtual bool IsPointInside(Float2) = 0;

	virtual void MatchRect(Rect) = 0;

	virtual Rect GetRect() = 0;


	void SetMainColor(RGBAFloat);

	void SetOutlineColor(RGBAFloat);

	Float2 GetCenter();

	float GetOutlineThickness();
	void SetOutlineThickness(float);

	protected:

	Float2 center;

	virtual void Draw() = 0;

	private:

	float outlineThickness;

	RGBAFloat fillColor;

	RGBAFloat outlineColor;

	void DrawFilled(RGBAFloat color);

	void DrawFilledOutlined(RGBAFloat fillColor, RGBAFloat borderColor, float thickness);

	void DrawOutlined(RGBAFloat color, float thickness);
};