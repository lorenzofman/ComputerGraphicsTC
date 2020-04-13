#include "EventSystem.h"
Callback<> EventSystem::UpdateCallback;
Callback<int> EventSystem::KeyDownCallback;
Callback<int> EventSystem::KeyUpCallback;
Callback<int, int, int, int, int, int> EventSystem::MouseUpdateCallback;

void EventSystem::OnUpdate()
{
	UpdateCallback.Invoke();
}

void EventSystem::OnKeyDown(int key)
{
	KeyDownCallback.Invoke(key);
}

void EventSystem::OnKeyUp(int key)
{
	KeyUpCallback.Invoke(key);
}

void EventSystem::OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y)
{
	MouseUpdateCallback.Invoke(button, state, wheel, direction, x, y);
}
