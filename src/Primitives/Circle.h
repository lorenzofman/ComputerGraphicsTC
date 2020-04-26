#pragma once

#include "Float2.h"
#include "Shape.h"
#include "RGBAFloat.h"
#include "../Canvas2D/Canvas2D.h"
class Circle : public Shape
{
	public:
	Circle(Float2 center, float radius);

	virtual bool IsPointInside(Float2 point) override;
	virtual void Draw(RGBAFloat color) override;
	virtual void Translate(Float2 delta) override;
	virtual void SetPosition(Float2 pos) override;
	
	private:
	float radius;
	Float2 center;
};