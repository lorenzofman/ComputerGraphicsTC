#pragma once

#include "../Shapes/Shape.h"
#include "../Primitives/Rect.h"
#include "../Canvas2D/Canvas2DExtensions.h"
#include "Button.h"
class ShapeTransformer : public IRenderable
{
	public:
	ShapeTransformer(Shape* shape = nullptr);
	
	void SetShape(Shape* shape);

	virtual void Render() override;

	void DrawTransformPoints(Rect& rect);

	Rect InflatePoint(Float2 center, float squareHalfSize);
	
	void DrawSurrondingRect(Rect& rect);

	void OnTopLeftDrag();
	void OnTopMiddleDrag();
	void OnTopRightDrag();

	void OnBottomLeftDrag();
	void OnBottomMiddleDrag();
	void OnBottomRightDrag();

	void OnLeftMiddleDrag();
	void OnRightMiddleDrag();

	void ApplyTransformation(Rect& newRect);
	bool IsMouseOver();

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
	Rect rect;
};

