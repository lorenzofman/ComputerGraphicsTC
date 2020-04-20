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

	World(ShapeTransformer&, ColorPalette&, ColorPalette&);

	private:

	enum class Key
	{
		Enter = 13,
		Ctrl_C = 3,
		Ctrl_E = 5,
		Ctrl_H = 8,
		Ctrl_I = 9,
		Ctrl_K = 11,
		Ctrl_O = 15,
		Ctrl_P = 16,
		Ctrl_R = 18,
		Ctrl_S = 19,
		Ctrl_T = 20,

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
		CreateCircle,
		CreateEquilatereumTriangle,
		CreateHexagon,
		CreateIsoscelesTriangle,
		CreateOctagon,
		CreatePentagon,
		CreateRectangle,
		CreateRectangleTriangle,
		MouseWheelUpdate,
		BringForward,
		SendBackward,
		Delete,
		Open,
		Save,
	};
	
	bool IsShiftPressed;
	bool IsAltPressed;
	bool IsCtrlPressed;

	/* If two keys are inputted between two frames the last one will prevail and the former won't have any effect */
	Input CurrentInput;
	InterfaceState CurrentState;
	
	Int2 MousePositionDelta;
	Int2 MousePosition;
	Shape* selectedShape;
	std::vector<Shape*> Shapes;
	ShapeTransformer& transformerRef;
	ColorPalette& mainColorPaletteRef;
	ColorPalette& outlineColorPaletteRef;

	void OnRender();
	void OnKeyDown(int key);
	void OnKeyUp(int key);
	void OnLeftMouseButtonDown();
	void OnMouseWheelUpdate();

	void RenderShapes();

	void ProcessState();
	void ProcessModifiers(int key, bool up);
	void ProcessInput(int key);
	
	void SelectedState();
	void IdleState();
	
	void SelectObject();
	Shape* GetFirstObjectMouseIsInside();
	void SetSelectedShape(Shape*);
	void UpdateOutlineThickness();
	void BringForward();
	void SendBackward();
	void GrabSelected();
	void RotateSelected();
	void ScaleSelected();
	bool ResultingRectIsBigEnough(float scaleDelta);
	void RemoveShape(Shape*);
	void Delete();
	void OpenFile();
	void SaveFile();
	void UpdateMainColor(RGBAFloat color);
	void UpdateOutlineColor(RGBAFloat color);

	void CreateCircle();

	void CreateRectangle();

	void CreateRectangleTriangle();
	void CreateTriangle(Float2* vertices);
	void CreatePolygon(const Array<Float2>& arr);
	void CreateIsoscelesTriangle();
	void CreateEquilatereumTriangle();
	
	void CreatePentagon();
	void CreateHexagon();
	void CreateOctagon();
	void CreateRegularPolygon(int vertices);
	void Message(const char* str);
};

void CaseInvariant(int& key);