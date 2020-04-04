#include "InterfaceButton.h"
#include "Canvas2D.h"


InterfaceButton::InterfaceButton(Scene* sc, InputHandler* in, const char* title, RGBFloat buttonColor, RGBFloat textColor, Rect2D rect, void(*OnClick)()) : Button(sc, in), IRenderable(sc)
{
	this->title = title;
	this->titleLength = strlen(title);
	this->buttonColor = buttonColor;
	this->textColor = textColor;
	this->rect = rect;
	this->OnClick = OnClick;
	this->interactable = true;
	this->visible = true;
	this->in = in;
}

void InterfaceButton::Render()
{
	if (visible == false)
	{
		return;
	}
	int canvas2DLetterSize = 10; // Check Canvas2D::DrawText for details
	bool mouseOver = rect.IsPointInside(in->GetMousePosition());
	float multiplier = interactable ? mouseOver ? 1 : 0.85f : 0.4f;
	Canvas2D::SetColor(buttonColor.r * multiplier, buttonColor.g * multiplier, buttonColor.b * multiplier);
	Canvas2D::DrawFilledRect((int) rect.BottomLeft.x, (int)rect.BottomLeft.y, (int)rect.TopRight.x, (int)rect.TopRight.y);
	Canvas2D::SetColor(textColor.r, textColor.g, textColor.b);
	int x = (int) (rect.BottomLeft.x + rect.TopRight.x) / 2;
	int y = (int) (rect.BottomLeft.y + rect.TopRight.y - canvas2DLetterSize) / 2;
	x -= (canvas2DLetterSize * titleLength) / 2;
	Canvas2D::DrawText(x, y, title);
}

void InterfaceButton::OnButtonDown()
{
	if (interactable && visible)
	{
		(*OnClick)();
	}
}
