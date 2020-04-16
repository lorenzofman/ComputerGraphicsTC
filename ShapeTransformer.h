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

	void OnTopLeftDrag(Float2 delta);
	void OnTopMiddleDrag(Float2 delta);
	void OnTopRightDrag(Float2 delta);

	void OnBottomLeftDrag(Float2 delta);
	void ApplyTransformation(Rect2D& newRect);
	void OnBottomMiddleDrag(Float2 delta);
	void OnBottomRightDrag(Float2 delta);

	void OnLeftMiddleDrag(Float2 delta);
	void OnRightMiddleDrag(Float2 delta);

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

