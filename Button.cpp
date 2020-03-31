#include "Button.h"
#include "Canvas2D.h"
Button::Button(Scene *sc, InputHandler* input, Rect2D rect, RGBFloat color) : ILeftMouseButtonUpListener(input), IRenderable(sc)
{
	this->rect = rect;
	this->color = color;
}

void Button::OnLeftMouseButtonUp(Float2 pos)
{
	if (rect.IsPointInside(pos))
	{
		OnButtonClicked();
	}
}

void Button::Render()
{
	Canvas2D::SetColor(color.r, color.g, color.b);
	Canvas2D::DrawFilledRect(
		(int)rect.BottomLeft.x, (int)rect.BottomLeft.y, 
		(int)rect.TopRight.x, (int)rect.TopRight.y);
}

void Button::OnButtonClicked()
{
}
