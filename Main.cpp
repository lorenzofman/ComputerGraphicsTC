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

std::string OpenFile()
{
	std::string filePath = FileDialog::Open();
	if (filePath.empty())
	{
		std::cout << "User cancelled opening the file";
		std::exit(EXIT_FAILURE);
	}
	return filePath;
}

std::string SaveFile()
{
	std::string filePath = FileDialog::Save();
	if (filePath.empty())
	{
		std::cout << "User cancelled saving the file";
		std::exit(EXIT_FAILURE);
	}
	return filePath;
}

int main()
{
	Image* userImage = ImageType::Read(OpenFile(), std::string("bmp"), Default, Input);
	int h = userImage->height, w = userImage->width;
	Canvas2D::Canvas2D(&h, &w, std::string("Lorenzo - T0"), OnKeyDown, OnKeyUp, OnMouseUpdate, OnRender);
}