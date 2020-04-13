#pragma once

#include "Shape.h"
#include "Rect.h"
#include "Canvas2DExtensions.h"
#include "Button.h"
class ShapeTransformer : public IRenderable
{
	public:
	ShapeTransformer(Shape* shape = nullptr);
	
	void SetShape(Shape* shape);

	virtual void Render() override;

	void DrawTransformPoints(Rect2D& rect);

	Rect2D InflatePoint(Float2 center, float squareHalfSize);
	
	void DrawSurrondingRect(Rect2D& rect);

	void OnLeftMouseButtonDown(Float2);
	void OnLeftMouseButtonUp(Float2);


	private:

	std::vector<Button*> buttons;
	Button* topLeft;
	Button* topMiddle;
	Button* topRight;
	Button* bottomLeft;
	Button* bottomMiddle;
	Button* bottomRight;
	Button* leftMiddle;
	Button* rightMiddle;
	Shape* shape;
};

