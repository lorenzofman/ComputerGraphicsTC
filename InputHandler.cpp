#include "InputHandler.h"
#include "IAnyKeyDownListener.h"
#include "IAnyKeyUpListener.h"
#include "IMouseListener.h"
#include <stdio.h>

InputHandler::InputHandler(Scene* sc) : IAnyKeyDownListener(sc), IAnyKeyUpListener(sc), IMouseListener(sc) { }

#pragma region Keyboard

void InputHandler::OnKeyDown(int key)
{
	if (keyDownListeners.find(key) == keyDownListeners.end())
	{
		return;
	}

	for (auto&& keyDown : keyDownListeners[key])
	{
		keyDown->OnKeyDown();
	}
}

void InputHandler::OnKeyUp(int key)
{
	if (keyUpListeners.find(key) == keyUpListeners.end())
	{
		return;
	}

	for (auto&& keyUp : keyUpListeners[key])
	{
		keyUp->OnKeyUp();
	}
}

void InputHandler::RegisterOnKeyDown(int key, IKeyDownListener* listener)
{
	if (keyDownListeners.find(key) == keyDownListeners.end())
	{
		keyDownListeners[key] = std::vector<IKeyDownListener*>();
	}
	keyDownListeners[key].push_back(listener);
}

void InputHandler::RegisterOnKeyUp(int key, IKeyUpListener* listener)
{
	if (keyUpListeners.find(key) == keyUpListeners.end())
	{
		keyUpListeners[key] = std::vector<IKeyUpListener*>();
	}
	keyUpListeners[key].push_back(listener);
}

#pragma endregion

#pragma region Specific Mouse Callbacks

void InputHandler::OnLeftMouseButtonDown()
{
	for (auto&& listener : leftMouseButtonDownListeners)
	{
		listener->OnLeftMouseButtonDown(mousePosition);
	}
}

void InputHandler::OnLeftMouseButtonUp()
{
	for (auto&& listener : leftMouseButtonUpListeners)
	{
		listener->OnLeftMouseButtonUp(mousePosition);
	}
}

void InputHandler::OnMiddleMouseButtonDown()
{
	for (auto&& listener : middleMouseButtonDownListeners)
	{
		listener->OnMiddleMouseButtonDown(mousePosition);
	}
}

void InputHandler::OnMiddleMouseButtonUp()
{
	for (auto&& listener : middleMouseButtonUpListeners)
	{
		listener->OnMiddleMouseButtonUp(mousePosition);
	}
}

void InputHandler::OnRightMouseButtonDown()
{
	for (auto&& listener : rightMouseButtonDownListeners)
	{
		listener->OnRightMouseButtonDown(mousePosition);
	}
}

void InputHandler::OnRightMouseButtonUp()
{
	for (auto&& listener : rightMouseButtonUpListeners)
	{
		listener->OnRightMouseButtonUp(mousePosition);
	}
}

void InputHandler::OnMouseWheelUpdate(MouseWheelDirection dir)
{
	for (auto&& listener : mouseWheelUpdateListeners)
	{
		listener->OnMouseWheelUpdate(dir);
	}
}

#pragma endregion

#pragma region Mouse

void InputHandler::MouseButtonsCallbacks(int button, int state)
{
	if (button < 0)
	{
		return;
	}
	(this->*mouseCallbacks[button][state])();
}

void InputHandler::MouseWheelCallback(int direction)
{
	if (direction == -2)
	{
		return;
	}
	OnMouseWheelUpdate((MouseWheelDirection) direction);
}

void InputHandler::OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y)
{
	mousePosition.x = (float) x;
	mousePosition.y = (float) y;
	MouseButtonsCallbacks(button, state);
	MouseWheelCallback(direction);
}

void InputHandler::RegisterLeftMouseButtonDownListener(ILeftMouseButtonDownListener* listener)
{
	leftMouseButtonDownListeners.push_back(listener);
}

void InputHandler::RegisterLeftMouseButtonUpListener(ILeftMouseButtonUpListener* listener)
{
	leftMouseButtonUpListeners.push_back(listener);
}

void InputHandler::RegisterRightMouseButtonDownListener(IRightMouseButtonDownListener* listener)
{
	rightMouseButtonDownListeners.push_back(listener);
}

void InputHandler::RegisterRightMouseButtonUpListener(IRightMouseButtonUpListener* listener)
{
	rightMouseButtonUpListeners.push_back(listener);
}

void InputHandler::RegisterMiddleMouseButtonDownListener(IMiddleMouseButtonDownListener* listener)
{
	middleMouseButtonDownListeners.push_back(listener);
}

void InputHandler::RegisterMiddleMouseButtonUpListener(IMiddleMouseButtonUpListener* listener)
{
	middleMouseButtonUpListeners.push_back(listener);
}

void InputHandler::RegisterMouseWheelUpdateListener(IMouseWheelUpdateListener* listener)
{
	mouseWheelUpdateListeners.push_back(listener);
}

Float2 InputHandler::GetMousePosition()
{
	return mousePosition;
}

#pragma endregion