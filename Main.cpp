
#include <iostream>
#include <string>
#include <vector>

#include "FileDialog.h"
#include "ImageType.h"
#include "Canvas2D.h"
#include "Constants.h"
#include "InputHandler.h"
Scene* PrimaryScene = new Scene();

void OnKeyDown(int key)
{
	PrimaryScene->OnKeyDownCallback(key);
}

void OnKeyUp(int key)
{
	PrimaryScene->OnKeyUpCallback(key);

}

void OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y)
{
	PrimaryScene->OnMouseUpdateCallback(button, state, wheel, direction, x, y);
}

void OnRender(void)
{
	PrimaryScene->OnRender();
}

std::string OpenFile(std::string extension)
{
	std::string filePath = FileDialog::Open(extension);
	if (filePath.empty())
	{
		std::cout << "User cancelled opening the file";
		std::exit(EXIT_FAILURE);
	}
	return filePath;
}

int main()
{
	std::string extension = std::string("bmp");
	Image* image = ImageType::Read(OpenFile(extension), extension, PrimaryScene);
	int h = image->height, w = image->width;
	image->position = Float2((float)image->width/2, (float)image->height/2);
	InputHandler input = InputHandler(PrimaryScene);
	Canvas2D::Canvas2D(&h, &w, std::string("Image Loader"), OnKeyDown, OnKeyUp, OnMouseUpdate, OnRender);
}