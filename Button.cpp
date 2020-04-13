#include "Button.h"

void Button::Render()
{
	Canvas2D::DrawFilledRect(rect.BottomLeft.x, rect.BottomLeft.y, rect.TopRight.x, rect.TopRight.y);
}

Button::Button(Rect2D rect)
{
	SetRect(rect);
}

bool Button::IsButtonPress(Float2 mousePosition)
{
	return rect.IsPointInside(mousePosition);
}

void Button::SetRect(Rect2D rect)
{
	this->rect = rect;
}
