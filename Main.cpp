#include <iostream>
#include <string>
#include <vector>

#include "FileDialog.h"
#include "ImageType.h"
#include "Canvas2D.h"
#include "Constants.h"
#include "InputHandler.h"
#include "ExtractChannel.h"
#include "Grayscale.h"
#include "ImageHistogram.h"
#include "Rect.h"
#include "Canvas2DExtensions.h"
#include "InterfaceButton.h"

#pragma region Global Declaring

Scene* Default;

InputHandler* Input;

Image* Primary;

RGBFloat ButtonColor;

RGBFloat ButtonTitleColor;

InterfaceButton* LoadButton;

InterfaceButton* SaveButton;


#pragma endregion

#pragma region Button Callbacks

void OnLoadButtonClick()
{
	std::string filePath = FileDialog::Open();
	if (filePath.empty())
	{
		return;
	}
	SaveButton->interactable = true;
	LoadButton->interactable = false;
	Primary = ImageType::Read(filePath, std::string("bmp"), Default, Input);
}

void OnSaveButtonClick()
{
	std::string filePath = FileDialog::Open();
	if (filePath.empty())
	{
		return;
	}
	Image* rasterized = Canvas2DExtensions::RasterizeImageTransformations(Primary, Default);
	delete Primary;
	Primary = rasterized;
	SaveButton->interactable = false;
	ImageType::Write(rasterized, filePath, std::string("bmp"));
}

#pragma endregion

#pragma region Callbacks

void OnKeyDown(int key)
{
	Default->OnKeyDownCallback(key);
}

void OnKeyUp(int key)
{
	Default->OnKeyUpCallback(key);
}

void OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y)
{
	Default->OnMouseUpdateCallback(button, state, wheel, direction, x, y);
}

void OnRender(void)
{
	Default->OnRender();
}

#pragma endregion

void InitializeWorld()
{
	Default = new Scene();
	Input = new InputHandler(Default);
	ButtonColor = RGBFloat(142.0F / 255.0F, 68.f / 255.f, 173.f / 255.f);
	ButtonTitleColor = RGBFloat(1, 1, 1);
	LoadButton = new InterfaceButton(Default, Input, "Open File", ButtonColor, ButtonTitleColor,
		Rect2D(0, 0, 150, 35), &OnLoadButtonClick);
	SaveButton = new InterfaceButton(Default, Input, "Save File", ButtonColor, ButtonTitleColor,
		Rect2D(160, 0, 310, 35), &OnSaveButtonClick);
	SaveButton->interactable = false;
}

int main()
{
	InitializeWorld();
	int h= 512, w = 512;
	Canvas2D::Canvas2D(&h, &w, std::string("Lorenzo - T0"), OnKeyDown, OnKeyUp, OnMouseUpdate, OnRender);
}