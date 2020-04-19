#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Screen.h"
#include "EventSystem.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Shape.h"
#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Constants.h"
#include "../Canvas2D/Canvas2DExtensions.h"
#include "../Helpers/Callback.h"
#include "../UI/ShapeTransformer.h"
#include "../Color/ColorPalette.h"
#include "../Serialization/ShapeSerializer.h"

class World
{
	public:

	static void BigBang();

	private:

	enum class Key
	{
		Enter = 13,
		Ctrl_C = 3,
		Ctrl_O = 15,
		Ctrl_P = 16,
		Ctrl_R = 18,
		Ctrl_S = 19,
		Num_0 = 48,
		Num_1 = 49,
		Num_2 = 50,
		Num_3 = 51,
		Num_4 = 52,
		Num_5 = 53,
		Num_6 = 54,
		Num_7 = 55,
		Num_8 = 56,
		Num_9 = 57,
		Colon = 58,
		B = 66,
		C = 67,
		E = 69,
		F = 70,
		G = 71,
		R = 82,
		S = 83,
		Delete = 127
	};

	enum class InterfaceState
	{
		Idle,
		ShapeSelected,
		Grabbing,
		Rotating,
		Scaling
	};

	enum class Input
	{
		None,
		Select,
		Confirm,
		Grab,
		Rotate,
		Scale,
		NewPolygon,
		NewCircle,
		NewRectangle,
		MouseWheelUpdate,
		ChangeColor,
		ChangeOutlineColor,
		BringForward,
		SendBackward,
		Delete,
		Open,
		Save,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Colon
	};
	
	static bool IsShiftPressed;
	static bool IsAltPressed;
	static bool IsCtrlPressed;

	/* If two keys are inputted between two frames the last one will prevail and the former won't have any effect */
	static Input CurrentInput;
	static InterfaceState CurrentState;
	
	static Int2 MousePositionDelta;
	static Int2 MousePosition;
	static int MouseScrollDelta;
	static Shape* SelectedShape;
	static std::vector<Shape*> Shapes;
	static ShapeTransformer Transformer;
	static ColorPalette MainColorPalette;
	static ColorPalette OutlineColorPalette;

	static void OnRender();
	static void OnKeyDown(int key);
	static void OnKeyUp(int key);
	static void OnLeftMouseButtonDown(Int2);
	static void OnMouseWheelUpdate();

	static void RenderShapes();

	static void ProcessState();
	static void ProcessModifiers(int key, bool up);
	static void ProcessInput(int key);
	
	static void SelectedState();
	static void IdleState();
	static void ListenToInput();
	
	static void SelectObject();
	static Shape* GetFirstObjectMouseIsInside();
	static void SetSelectedShape(Shape*);
	static void UpdateOutlineThickness();
	static void BringForward();
	static void SendBackward();
	static void GrabSelected();
	static void RotateSelected();
	static void ScaleSelected();
	static bool ResultingRectIsBigEnough(float scaleDelta);
	static void RemoveShape(Shape*);
	static void Delete();
	static void OpenFile();
	static void SaveFile();
	static void UpdateMainColor(RGBAFloat color);
	static void UpdateOutlineColor(RGBAFloat color);


	static void CreateCircle();

	static void CreateRectangle();

	static void Message(const char* str);
};

void CaseInvariant(int& key);