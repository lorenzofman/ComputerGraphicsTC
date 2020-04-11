#pragma once

#include "Shape.h"
#include "Rect.h"
class ShapeTransformer : public IRenderable
{
	public:
	ShapeTransformer(Shape* shape = nullptr);
	
	void SetShape(Shape* shape);

	virtual void Render() override;

	private:
	
	Shape* shape;
};

