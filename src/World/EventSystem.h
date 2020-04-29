#pragma once

#include <chrono>
#include <thread>
#include <iostream>

#include "../Helpers/Callback.h"

#include "../Primitives/Int2.h"

#include "../Primitives/Constants.h"

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
	static void Configure();
	static void OnUpdate();
	static void OnKeyDown(int key);
	static void OnKeyUp(int key);
	static void OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y);

	static void MouseButtonClick(Callback<> downCallback, Callback<> upCallback, EventSystem::MouseButtonState btnState);

	static Callback<> UpdateCallback;
	static Callback<int> KeyDownCallback;
	static Callback<int> KeyUpCallback;
	static Callback<int, int, int, int, int, int> MouseUpdateCallback;

	static Callback<> LeftMouseButtonDownCallback;
	static Callback<> LeftMouseButtonUpCallback;

	static Callback<> MiddleMouseButtonDownCallback;
	static Callback<> MiddleMouseButtonUpCallback;

	static Callback<> RightMouseButtonDownCallback;
	static Callback<> RightMouseButtonUpCallback;

	static Callback<> MouseMovementCallback;
	static Callback<> MouseWheelCallback;

	static Int2 MousePosition;
	static Int2 MousePositionDelta;
	static int MouseScrollDelta;
};