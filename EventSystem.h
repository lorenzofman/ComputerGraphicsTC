#pragma once
#include <functional>
#include "Callback.h"
class EventSystem
{
	public:
	static void OnUpdate();
	static void OnKeyDown(int key);
	static void OnKeyUp(int key);
	static void OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y);
	
	static Callback<> UpdateCallback;
	static Callback<int> KeyDownCallback;
	static Callback<int> KeyUpCallback;
	static Callback<int, int, int, int, int, int> MouseUpdateCallback;
};