#include "ColorPalette.h"


ColorPalette::ColorPalette() : ColorPalette(Float2()) { }

ColorPalette::ColorPalette(Float2 buttonPosition)
{
	this->position = buttonPosition;
	this->open = false;
	this->colorButton = new Button(Colors::Default, Rect(buttonPosition, Colors::Palette::ButtonHalfSize));
	this->colorButton->ClickCallback.Register([this](Button* btn) {this->OnOpenPalette(); });
	CreateButtons();
}

void ColorPalette::Render()
{
	colorButton->Render();
	for (const auto & kv : buttons)
	{
		kv.first->Render();
	}
}

void ColorPalette::OnOpenPalette()
{
    for (const auto & kv : buttons)
    {
        kv.first->active = true;
    }
	open = true;
}

void ColorPalette::ClosePalette()
{
	for (const auto & kv : buttons)
    {
        kv.first->active = false;
    }
	open = false;
}

void ColorPalette::OnColorClick(Button* btn)
{
	RGBAFloat color = buttons[btn];
	this->colorButton->color = color;
	colorUpdateCallback.Invoke(color);
	ClosePalette();
}

RGBAFloat ColorPalette::GetCurrentColor()
{
	return colorButton->color;
}

bool ColorPalette::IsMouseOver()
{
	if (colorButton->rect.IsPointInside(EventSystem::MousePosition))
	{
		return true;
	}
	if (open == false)
	{
		return false;
	}
	for (const auto& kv : buttons)
	{
		if (kv.first->rect.IsPointInside(EventSystem::MousePosition))
		{
			return true;
		}
	}
	return false;
}

void ColorPalette::CreateButtons()
{
	for (int i = 0; i < Colors::Palette::Height; i++)
	{
		for (int j = 0; j < Colors::Palette::Width; j++)
		{
			int idx = i * Colors::Palette::Width + j;
			RGBAFloat color = Colors::Palette::Colors[idx];
			Rect rect = CalculateRectangle(i, j);
			rect.Translate(Float2(position.x - Colors::Palette::ButtonHalfSize, Colors::Palette::ButtonHalfSize * 2));
			Button* btn = new Button(color, rect);
			btn->ClickCallback.Register([this](Button* btn) {this->OnColorClick(btn); });
			btn->active = false;
			buttons[btn] = color;
		}
	}
}
/*
Top -> Down
Left-> Right
*/
Rect ColorPalette::CalculateRectangle(int i, int j)
{
	int heightStep = (Colors::Palette::ColorHeight);
	int widthStep = (Colors::Palette::ColorWidth);
	int paletteHeight = Colors::Palette::Height * heightStep;
	int yStart = paletteHeight - (i + 1) * heightStep;
	int yEnd = paletteHeight - i * heightStep;
	int xStart = widthStep * j;
	int xEnd = widthStep * (j + 1);
	return Rect((float) xStart, (float) yStart, (float) xEnd, (float) yEnd);
}
