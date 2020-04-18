#include "ShapeTransformer.h"
#include <iostream>
ShapeTransformer::ShapeTransformer(Shape* shape)
{
	SetShape(shape);
	buttons.push_back(topLeft = new Button(Colors::Selection));
	buttons.push_back(topMiddle = new Button(Colors::Selection));
	buttons.push_back(topRight = new Button(Colors::Selection));
	buttons.push_back(bottomLeft = new Button(Colors::Selection));
	buttons.push_back(bottomMiddle = new Button(Colors::Selection));
	buttons.push_back(bottomRight = new Button(Colors::Selection));
	buttons.push_back(leftMiddle = new Button(Colors::Selection));
	buttons.push_back(rightMiddle = new Button(Colors::Selection));

	topLeft->DragCallback.Register([this](Button*) {this->OnTopLeftDrag(); });
	topMiddle->DragCallback.Register([this](Button*) {this->OnTopMiddleDrag(); });
	topRight->DragCallback.Register([this](Button*) {this->OnTopRightDrag(); });

	bottomLeft->DragCallback.Register([this](Button*) {this->OnBottomLeftDrag(); });
	bottomMiddle->DragCallback.Register([this](Button*) {this->OnBottomMiddleDrag(); });
	bottomRight->DragCallback.Register([this](Button*) {this->OnBottomRightDrag(); });

	leftMiddle->DragCallback.Register([this](Button*) {this->OnLeftMiddleDrag(); });
	rightMiddle->DragCallback.Register([this](Button*) {this->OnRightMiddleDrag(); });

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
	this->rect = rect;
	
	Float2 middleUpPoint = (rect.TopLeft + rect.TopRight) * 0.5f;
	Float2 middleDownPoint = (rect.BottomLeft + rect.BottomRight) * 0.5f;
	Float2 middleLeftPoint = (rect.BottomLeft + rect.TopLeft) * 0.5f;
	Float2 middleRightPoint = (rect.BottomRight + rect.TopRight) * 0.5f;
	

	topRight->rect = InflatePoint(rect.TopRight, TransfomerEdgeHalfSize);
	topLeft->rect = InflatePoint(rect.TopLeft, TransfomerEdgeHalfSize);
	bottomLeft->rect = InflatePoint(rect.BottomLeft, TransfomerEdgeHalfSize);
	bottomRight->rect = InflatePoint(rect.BottomRight, TransfomerEdgeHalfSize);

	topMiddle->rect = InflatePoint(middleUpPoint, TransformerSideHalfSize);
	bottomMiddle->rect = InflatePoint(middleDownPoint, TransformerSideHalfSize);
	leftMiddle->rect = InflatePoint(middleLeftPoint, TransformerSideHalfSize);
	rightMiddle->rect = InflatePoint(middleRightPoint, TransformerSideHalfSize);

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
	Canvas2DExtensions::DrawThickLine(rect.BottomLeft, rect.BottomRight, Colors::Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.BottomRight, rect.TopRight, Colors::Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopRight, rect.TopLeft, Colors::Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopLeft, rect.BottomLeft, Colors::Selection, SelectionThickness);
}

void ShapeTransformer::OnTopLeftDrag()
{
	Rect2D newRect = Rect2D::TopLeftBottomRight(EventSystem::MousePosition, rect.BottomRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnTopRightDrag()
{
	Rect2D newRect = Rect2D(rect.BottomLeft, EventSystem::MousePosition);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnBottomLeftDrag()
{
	Rect2D newRect = Rect2D(EventSystem::MousePosition, rect.TopRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnBottomRightDrag()
{
	Rect2D newRect = Rect2D::TopLeftBottomRight(rect.TopLeft, EventSystem::MousePosition);
	ApplyTransformation(newRect);
}

void ShapeTransformer::OnTopMiddleDrag()
{
	Rect2D newRect = Rect2D(rect.BottomLeft, Float2(rect.TopRight.x, EventSystem::MousePosition.y));
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnBottomMiddleDrag()
{
	Rect2D newRect = Rect2D(Float2(rect.BottomLeft.x, EventSystem::MousePosition.y), rect.TopRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnLeftMiddleDrag()
{
	Rect2D newRect = Rect2D(Float2(EventSystem::MousePosition.x, rect.BottomLeft.y), rect.TopRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnRightMiddleDrag()
{
	Rect2D newRect = Rect2D(rect.BottomLeft, Float2(EventSystem::MousePosition.x, rect.TopRight.y));
	ApplyTransformation(newRect);
}

void ShapeTransformer::ApplyTransformation(Rect2D& newRect)
{
	shape->MatchRect(newRect);
}

bool ShapeTransformer::IsPointInsideAnyTransformerButton(Int2 mousePos)
{
	for (auto&& btn : buttons)
	{
		if (btn->rect.IsPointInside(mousePos))
		{
			return true;
		}
	}
	return false;
}
