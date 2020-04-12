#include "ShapeTransformer.h"

ShapeTransformer::ShapeTransformer(Shape* shape)
{
	SetShape(shape);
}

void ShapeTransformer::SetShape(Shape* shape)
{
	this->shape = shape;
}

void ShapeTransformer::Render()
{
	if (shape == nullptr)
	{
		return;
	}
	Rect2D rect = shape->GetRect();

	DrawSurrondingRect(rect);
	DrawTransformPoints(rect);
}

void ShapeTransformer::DrawTransformPoints(Rect2D& rect)
{
	Float2 middleUpPoint = (rect.TopLeft() + rect.TopRight) * 0.5f;
	Float2 middleDownPoint = (rect.BottomLeft + rect.BottomRight()) * 0.5f;
	Float2 middleLeftPoint = (rect.BottomLeft + rect.TopLeft()) * 0.5f;
	Float2 middleRightPoint = (rect.BottomRight() + rect.TopRight) * 0.5f;

	Rect2D topRight = InflatePoint(rect.TopRight, TransfomerEdgeHalfSize);
	Rect2D topLeft = InflatePoint(rect.TopLeft(), TransfomerEdgeHalfSize);
	Rect2D bottomLeft = InflatePoint(rect.BottomLeft, TransfomerEdgeHalfSize);
	Rect2D bottomRight = InflatePoint(rect.BottomRight(), TransfomerEdgeHalfSize);

	Rect2D middleUp = InflatePoint(middleUpPoint, TransformerSideHalfSize);
	Rect2D middleDown = InflatePoint(middleDownPoint, TransformerSideHalfSize);
	Rect2D middleLeft = InflatePoint(middleLeftPoint, TransformerSideHalfSize);
	Rect2D middleRight = InflatePoint(middleRightPoint, TransformerSideHalfSize);

	DrawRect(topRight);
	DrawRect(topLeft);
	DrawRect(bottomLeft);
	DrawRect(bottomRight);

	DrawRect(middleUp);
	DrawRect(middleDown);
	DrawRect(middleLeft);
	DrawRect(middleRight);

}

Rect2D ShapeTransformer::InflatePoint(Float2 center, float squareHalfSize)
{
	return Rect2D(center.x - squareHalfSize, center.y - squareHalfSize, center.x + squareHalfSize, center.y +squareHalfSize);
}

void ShapeTransformer::DrawRect(Rect2D& rect)
{
	Canvas2D::DrawFilledRect(rect.BottomLeft.x, rect.BottomLeft.y, rect.TopRight.x, rect.TopRight.y);
}


void ShapeTransformer::DrawSurrondingRect(Rect2D& rect)
{
	Canvas2DExtensions::DrawThickLine(rect.BottomLeft, rect.BottomRight(), Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.BottomRight(), rect.TopRight, Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopRight, rect.TopLeft(), Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopLeft(), rect.BottomLeft, Selection, SelectionThickness);
}

