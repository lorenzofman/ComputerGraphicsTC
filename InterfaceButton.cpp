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
}

void InterfaceButton::Render()
{
	int canvas2DLetterSize = 10;
	Canvas2D::SetColor(buttonColor.r, buttonColor.g, buttonColor.b);
	Canvas2D::DrawFilledRect((int) rect.BottomLeft.x, (int)rect.BottomLeft.y, (int)rect.TopRight.x, (int)rect.TopRight.y);
	Canvas2D::SetColor(textColor.r, textColor.g, textColor.b);
	int x = (rect.BottomLeft.x + rect.TopRight.x) / 2;
	int y = (rect.BottomLeft.y + rect.TopRight.y - canvas2DLetterSize) / 2;
	x -= (canvas2DLetterSize * titleLength) / 2;// Canvas2D character offset
	Canvas2D::DrawText(x, y, title);
}

void InterfaceButton::OnButtonDown()
{
	(*OnClick)();
}
