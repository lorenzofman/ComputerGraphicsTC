#pragma once

#include "Shape.h"
#include "Rect.h"
#include "Canvas2DExtensions.h"

class ShapeTransformer : public IRenderable
{
	public:
	ShapeTransformer(Shape* shape = nullptr);
	
	void SetShape(Shape* shape);

	virtual void Render() override;

	void DrawTransformPoints(Rect2D& rect);

	Rect2D InflatePoint(Float2 center, float squareHalfSize);
	
	void DrawRect(Rect2D& rect);
	
	void DrawSurrondingRect(Rect2D& rect);

	private:
	
	Shape* shape;
};

