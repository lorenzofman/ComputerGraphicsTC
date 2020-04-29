
#include "EventSystem.h"


std::chrono::steady_clock::time_point lastTime;
Int2 EventSystem::MousePosition;
Int2 EventSystem::MousePositionDelta;
int EventSystem::MouseScrollDelta = 0;

Callback<> EventSystem::UpdateCallback;
Callback<int> EventSystem::KeyDownCallback;
Callback<int> EventSystem::KeyUpCallback;
Callback<int, int, int, int, int, int> EventSystem::MouseUpdateCallback;

Callback<> EventSystem::LeftMouseButtonDownCallback;
Callback<> EventSystem::LeftMouseButtonUpCallback;

Callback<> EventSystem::MiddleMouseButtonDownCallback;
Callback<> EventSystem::MiddleMouseButtonUpCallback;

Callback<> EventSystem::RightMouseButtonDownCallback;
Callback<> EventSystem::RightMouseButtonUpCallback;

Callback<> EventSystem::MouseMovementCallback;
Callback<> EventSystem::MouseWheelCallback;

void EventSystem::Configure()
{
	lastTime = std::chrono::steady_clock::now();
}

void EventSystem::OnUpdate()
{
	int targetMilisecondsPerFrame = 1000 / TargetFramesPerSeconds;
	int targetMicrosecondsPerFrame = targetMilisecondsPerFrame * 1000;
	auto current = std::chrono::steady_clock::now();
	long long duration = std::chrono::duration_cast<std::chrono::microseconds>(current - lastTime).count();
	if (duration < targetMicrosecondsPerFrame)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(targetMicrosecondsPerFrame - duration));
	}
	lastTime = std::chrono::steady_clock::now();
	UpdateCallback.Invoke();
	MousePositionDelta = Int2(0, 0);
	MouseScrollDelta = 0;
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
	MouseScrollDelta = (wheel == 0) ? direction : 0;
	MousePositionDelta = Int2(x, y) - MousePosition;
	MousePosition = Int2(x, y);

	MouseUpdateCallback.Invoke(button, state, wheel, direction, x, y);

	MouseButton btn = (MouseButton)button;
	MouseButtonState btnState = (MouseButtonState)state;

	switch (btn)
	{
		case EventSystem::MouseButton::Left:
			MouseButtonClick(LeftMouseButtonDownCallback, LeftMouseButtonUpCallback, btnState);
			break;
		case EventSystem::MouseButton::Middle:
			MouseButtonClick(MiddleMouseButtonDownCallback, MiddleMouseButtonUpCallback, btnState);
			break;
		case EventSystem::MouseButton::Right:
			MouseButtonClick(RightMouseButtonDownCallback, RightMouseButtonUpCallback, btnState);
			break;
		default:
			break;
	}
	
	if (MousePositionDelta != Int2(0,0))
	{
		MouseMovementCallback.Invoke();
	}

	if (direction != 0 && direction != -2)
	{
		MouseWheelCallback.Invoke();
	}
}

void EventSystem::MouseButtonClick(Callback<> downCallback, Callback<> upCallback, EventSystem::MouseButtonState btnState)
{
	switch (btnState)
	{
		case EventSystem::MouseButtonState::Down:
			downCallback.Invoke();
			break;
		case EventSystem::MouseButtonState::Up:
			upCallback.Invoke();
			break;
		default:
			break;
	}
}
