#include "ColorPalette.h"

ColorPalette::ColorPalette(Float2 buttonPosition)
{
	this->position = buttonPosition;
	colorButton = new Button(Colors::Default, Rect2D(buttonPosition, Colors::Palette::ButtonHalfSize));
	colorButton->ClickCallback.Register([this](Button* btn) {this->OnOpenPalette(); });
	CreateButtons();
	//colorButton->ClickCallback.Register([this](Button* btn) {this->OnColorClick(btn); });
}

void ColorPalette::Render()
{
	//colorButton->Render();
	for (const auto & [buttonPtr, color] : buttons) 
	{
		buttonPtr->Render();
	}
}

void ColorPalette::OnOpenPalette()
{

}

void ColorPalette::OnColorClick(Button* btn)
{

}

void ColorPalette::CreateButtons()
{
	for (int i = 0; i < Colors::Palette::Height; i++)
	{
		for (int j = 0; j < Colors::Palette::Width; j++)
		{
			int idx = i * Colors::Palette::Width + j;
			RGBAFloat color = Colors::Palette::Colors[idx];
			Rect2D rect = CalculateRectangle(i, j);
			rect.Translate(Float2(Colors::Palette::ButtonHalfSize * 2, Colors::Palette::ButtonHalfSize * 2));
			Button* btn = new Button(color, rect);
			buttons[btn] = color;
		}
	}
}
/* 
Top -> Down
Left-> Right
*/
Rect2D ColorPalette::CalculateRectangle(int i, int j)
{
	int heightStep = (Colors::Palette::ColorHeight);
	int widthStep = (Colors::Palette::ColorWidth);
	int paletteHeight = Colors::Palette::Height * heightStep;
	int yStart = paletteHeight - (i + 1) * heightStep;
	int yEnd = paletteHeight - i * heightStep;
	int xStart = widthStep * j;
	int xEnd = widthStep * (j + 1);
	return Rect2D((float) xStart, (float) yStart, (float) xEnd, (float) yEnd);
}
