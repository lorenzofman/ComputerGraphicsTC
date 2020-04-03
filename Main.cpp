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
Scene* Default = new Scene();
InputHandler* Input = new InputHandler(Default);

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

void OnLoadButtonClick()
{
	std::string filePath = FileDialog::Open();
	if (filePath.empty())
	{
		return;
	}
	Image* userImage = ImageType::Read(filePath, std::string("bmp"), Default, Input);
}

int main()
{
	int h= 512, w = 512;
	RGBFloat buttonColor = RGBFloat(142.0F / 255.0F, 68.f / 255.f, 173.f / 255.f);
	RGBFloat buttonTitleColor = RGBFloat(1, 1, 1);
	InterfaceButton* saveButton = new InterfaceButton(Default, Input, "Open File", buttonColor, buttonTitleColor,
		Rect2D(0, 0, 150, 35), &OnLoadButtonClick);
	Canvas2D::Canvas2D(&h, &w, std::string("Lorenzo - T0"), OnKeyDown, OnKeyUp, OnMouseUpdate, OnRender);
}