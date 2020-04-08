#pragma once

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <string>
#include <cmath>

#include "Float2.h"
#include "RGBAFloat.h"
#undef DrawText /* DrawText conflicts with WinUser.h header*/

class Canvas2D
{
	public:

	Canvas2D(int*, int*, std::string,
		void(OnKeyDownCallback(int)),
		void(OnKeyUpCallback(int)),
		void(OnMouseUpdateCallback(int, int, int, int, int, int)),
		void(OnRender(void)));

	static void DrawPoint(int, int);
	static void DrawLine(int, int, int, int);

	static void DrawRect(int, int, int, int);
	static void DrawFilledRect(int, int, int, int);

	static void DrawPolygon(Float2 vertices[], int);
	static void DrawFilledPolygon(Float2 vertices[], int);

	static void DrawCircle(Float2 pos, float radius, int divisions);
	static void DrawFilledCircle(Float2 pos, float radius, int divisions);

	static void DrawText(int, int, const char*);

	static void SetColor(RGBAFloat color);
	static void ClearScreen(RGBAFloat color);

	private:

	static int* scrWidth;
	static int* scrHeight;

	static void (*OnKeyDownCallback)(int);
	static void (*OnKeyUpCallback)(int);
	static void (*OnMouseUpdateCallback)(int, int, int, int, int, int);
	static void (*OnRenderCallback)(void);

	static void OnSpecialKeyDown(int, int, int);

	static void OnSpecialKeyUp(int, int, int);

	static void OnKeyboardDownGlutCallback(unsigned char, int, int);

	static void OnKeyboardUpGlutCallback(unsigned char, int, int);

	static void OnMouseClick(int, int, int, int);

	static void OnMouseWheel(int, int, int, int);

	static void OnMouseMotion(int, int);

	static void ConvertMouseCoord(int, int, int, int, int, int);

	static void ScreenRedimensionCallback(int, int);

	static void Display();

	static void RunCanvas();
};
