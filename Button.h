#pragma once

#include "IRenderable.h"
#include "Rect.h"
#include "Canvas2D.h"

class Button : public IRenderable
{
	public:
	
	Button(Rect2D rect = Rect2D());

	bool IsButtonPress(Float2 mousePosition);

	void SetRect(Rect2D rect);

	// Inherited via IRenderable
	virtual void Render() override;

	private:
	Rect2D rect;
};

