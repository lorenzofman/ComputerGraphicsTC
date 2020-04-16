#pragma once

#include "Callback.h"

#include "Int2.h"

class EventSystem
{
	public:

	enum class MouseButton
	{
		Left = 0,
		Middle = 1,
		Right = 2
	};

	enum class MouseButtonState
	{
		Down = 0,
		Up = 1
	};

	static void OnUpdate();
	static void OnKeyDown(int key);
	static void OnKeyUp(int key);
	static void OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y);

	static void MouseButtonClick(Callback<Int2> downCallback, Callback<Int2> upCallback, EventSystem::MouseButtonState btnState);

	static Callback<> UpdateCallback;
	static Callback<int> KeyDownCallback;
	static Callback<int> KeyUpCallback;
	static Callback<int, int, int, int, int, int> MouseUpdateCallback;

	static Callback<Int2> LeftMouseButtonDownCallback;
	static Callback<Int2> LeftMouseButtonUpCallback;

	static Callback<Int2> MiddleMouseButtonDownCallback;
	static Callback<Int2> MiddleMouseButtonUpCallback;

	static Callback<Int2> RightMouseButtonDownCallback;
	static Callback<Int2> RightMouseButtonUpCallback;

	static Callback<Int2> MouseMovementCallback;
	static Callback<int> MouseWheelCallback;

	static Int2 MousePosition;
	static Int2 MousePositionDelta;
	static int MouseScrollDelta;
};