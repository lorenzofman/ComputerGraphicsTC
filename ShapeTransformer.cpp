#include "ShapeTransformer.h"

ShapeTransformer::ShapeTransformer(Shape* shape)
{
	SetShape(shape);
	buttons.push_back(topLeft = new Button());
	buttons.push_back(topMiddle = new Button());
	buttons.push_back(topRight = new Button());
	buttons.push_back(bottomLeft = new Button());
	buttons.push_back(bottomMiddle = new Button());
	buttons.push_back(bottomRight = new Button());
	buttons.push_back(leftMiddle = new Button());
	buttons.push_back(rightMiddle = new Button());
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

	topRight->SetRect(InflatePoint(rect.TopRight, TransfomerEdgeHalfSize));
	topLeft->SetRect(InflatePoint(rect.TopLeft(), TransfomerEdgeHalfSize));
	bottomLeft->SetRect(InflatePoint(rect.BottomLeft, TransfomerEdgeHalfSize));
	bottomRight->SetRect(InflatePoint(rect.BottomRight(), TransfomerEdgeHalfSize));

	topMiddle->SetRect(InflatePoint(middleUpPoint, TransformerSideHalfSize));
	bottomMiddle->SetRect(InflatePoint(middleDownPoint, TransformerSideHalfSize));
	leftMiddle->SetRect(InflatePoint(middleLeftPoint, TransformerSideHalfSize));
	rightMiddle->SetRect(InflatePoint(middleRightPoint, TransformerSideHalfSize));

	for (auto&& btn : buttons) 
	{
		btn->Render();
	}

}

Rect2D ShapeTransformer::InflatePoint(Float2 center, float squareHalfSize)
{
	return Rect2D(center.x - squareHalfSize, center.y - squareHalfSize, center.x + squareHalfSize, center.y +squareHalfSize);
}

void ShapeTransformer::DrawSurrondingRect(Rect2D& rect)
{
	Canvas2DExtensions::DrawThickLine(rect.BottomLeft, rect.BottomRight(), Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.BottomRight(), rect.TopRight, Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopRight, rect.TopLeft(), Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopLeft(), rect.BottomLeft, Selection, SelectionThickness);
}