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

	void OnTopLeftDrag();
	void OnTopMiddleDrag();
	void OnTopRightDrag();

	void OnBottomLeftDrag();
	void OnBottomMiddleDrag();
	void OnBottomRightDrag();

	void OnLeftMiddleDrag();
	void OnRightMiddleDrag();

	void ApplyTransformation(Rect2D& newRect);
	bool IsPointInsideAnyTransformerButton(Int2);

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
	Rect2D rect;
};

