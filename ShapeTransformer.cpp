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
	Rect2D rect = shape->GetRect();
}
