#include "ShapeTransformer.h"
#include <iostream>
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

	topLeft->DragCallback.Register([this](Int2 delta) {this->OnTopLeftDrag(delta); });
	topMiddle->DragCallback.Register([this](Int2 delta) {this->OnTopMiddleDrag(delta); });
	topRight->DragCallback.Register([this](Int2 delta) {this->OnTopRightDrag(delta); });

	bottomLeft->DragCallback.Register([this](Int2 delta) {this->OnBottomLeftDrag(delta); });
	bottomMiddle->DragCallback.Register([this](Int2 delta) {this->OnBottomMiddleDrag(delta); });
	bottomRight->DragCallback.Register([this](Int2 delta) {this->OnBottomRightDrag(delta); });

	leftMiddle->DragCallback.Register([this](Int2 delta) {this->OnLeftMiddleDrag(delta); });
	rightMiddle->DragCallback.Register([this](Int2 delta) {this->OnRightMiddleDrag(delta); });

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
	Canvas2DExtensions::DrawThickLine(rect.BottomLeft, rect.BottomRight, Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.BottomRight, rect.TopRight, Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopRight, rect.TopLeft, Selection, SelectionThickness);
	Canvas2DExtensions::DrawThickLine(rect.TopLeft, rect.BottomLeft, Selection, SelectionThickness);
}
void ShapeTransformer::OnTopLeftDrag(Float2 delta)
{
	Rect2D newRect = Rect2D::TopLeftBottomRight(EventSystem::MousePosition, rect.BottomRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnTopRightDrag(Float2 delta)
{
	Rect2D newRect = Rect2D(rect.BottomLeft, EventSystem::MousePosition);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnBottomLeftDrag(Float2 delta)
{
	Rect2D newRect = Rect2D(EventSystem::MousePosition, rect.TopRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnBottomRightDrag(Float2 delta)
{
	Rect2D newRect = Rect2D::TopLeftBottomRight(rect.TopLeft, EventSystem::MousePosition);
	ApplyTransformation(newRect);
}

void ShapeTransformer::OnTopMiddleDrag(Float2 delta)
{
	Rect2D newRect = Rect2D(rect.BottomLeft, Float2(rect.TopRight.x, EventSystem::MousePosition.y));
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnBottomMiddleDrag(Float2 delta)
{
	Rect2D newRect = Rect2D(Float2(rect.BottomLeft.x, EventSystem::MousePosition.y), rect.TopRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnLeftMiddleDrag(Float2 delta)
{
	Rect2D newRect = Rect2D(Float2(EventSystem::MousePosition.x, rect.BottomLeft.y), rect.TopRight);
	ApplyTransformation(newRect);
}
void ShapeTransformer::OnRightMiddleDrag(Float2 delta)
{
	Rect2D newRect = Rect2D(rect.BottomLeft, Float2(EventSystem::MousePosition.x, rect.TopRight.y));
	ApplyTransformation(newRect);
}

void ShapeTransformer::ApplyTransformation(Rect2D& newRect)
{
	newRect.rotation = this->rect.rotation;
	float oldWidth = rect.TopRight.x - rect.BottomLeft.x;
	float newWidth = newRect.TopRight.x - newRect.BottomLeft.x;

	float oldHeight = rect.TopRight.y - rect.BottomLeft.y;
	float newHeight = newRect.TopRight.y - newRect.BottomLeft.y;

	float dx = newWidth - oldWidth;
	float dy = newHeight - oldHeight;
	
	float ddx = newWidth / oldWidth;
	float ddy = newHeight / oldHeight;
	float max = fmaxf(ddx, ddy);

	Float2 newCenter = newRect.Center();
	Float2 oldCenter = this->rect.Center();
	Float2 dif = newCenter - oldCenter;
	//shape->Scale(max);
	shape->Translate(dif);
	shape->Scale(ddx, ddy);
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
