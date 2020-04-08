#include <iostream>
#include <string>
#include <vector>

#include "FileDialog.h"
#include "Canvas2D.h"
#include "Constants.h"
#include "Types.h"
void OnKeyDown(int key)
{
}

void OnKeyUp(int key)
{
}

void OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y)
{
}

void OnRender()
{
}

int main()
{
	Callback<void> callback = &OnRender;
	int w = 512; int h = 512;
	Canvas2D(&w, &h, std::string("Lorenzo - TB"), OnKeyDown, OnKeyUp, OnMouseUpdate, OnRender);
}
