#include "Button.h"
#include "Canvas2D.h"
Button::Button(Scene *sc, InputHandler* input) : ILeftMouseButtonDownListener(input), ILeftMouseButtonUpListener(input)
{
	this->rect = rect;
	this->color = color;
}

void Button::OnLeftMouseButtonUp(Float2 pos)
{
	if (rect.IsPointInside(pos))
	{
		OnButtonUp();
	}
}

void Button::OnLeftMouseButtonDown(Float2 pos)
{
	if (rect.IsPointInside(pos))
	{
		OnButtonDown();
	}
}

void Button::OnButtonDown() { } // virtual
void Button::OnButtonUp() { } // virtual