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

/* Iterations need to be done with indexed loops because callbacks might create new instances that register to this class */
/* When an instance register it changes the collection invalidating the iterator and throwing an exception */
void InputHandler::OnLeftMouseButtonDown()
{
	for (auto i = 0; i < leftMouseButtonDownListeners.size(); i++)
	{
		leftMouseButtonDownListeners[i]->OnLeftMouseButtonDown(mousePosition);
	}
}

void InputHandler::OnLeftMouseButtonUp()
{
	for (auto i = 0; i < leftMouseButtonUpListeners.size(); i++)
	{
		leftMouseButtonUpListeners[i]->OnLeftMouseButtonUp(mousePosition);
	}
}

void InputHandler::OnMiddleMouseButtonDown()
{
	for (auto i = 0; i < middleMouseButtonDownListeners.size(); i++)
	{
		middleMouseButtonDownListeners[i]->OnMiddleMouseButtonDown(mousePosition);
	}
}

void InputHandler::OnMiddleMouseButtonUp()
{
	for (auto i = 0; i < middleMouseButtonUpListeners.size(); i++)
	{
		middleMouseButtonUpListeners[i]->OnMiddleMouseButtonUp(mousePosition);
	}
}

void InputHandler::OnRightMouseButtonDown()
{
	for (auto i = 0; i < rightMouseButtonDownListeners.size(); i++)
	{
		rightMouseButtonDownListeners[i]->OnRightMouseButtonDown(mousePosition);
	}
}

void InputHandler::OnRightMouseButtonUp()
{
	for (auto i = 0; i < rightMouseButtonUpListeners.size(); i++)
	{
		rightMouseButtonUpListeners[i]->OnRightMouseButtonUp(mousePosition);
	}
}

void InputHandler::OnMouseWheelUpdate(MouseWheelDirection dir)
{
	for (auto i = 0; i < mouseWheelUpdateListeners.size(); i++)
	{
		mouseWheelUpdateListeners[i]->OnMouseWheelUpdate(dir);
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

void InputHandler::DeregisterLeftMouseButtonDownListener(ILeftMouseButtonDownListener* listener)
{
	leftMouseButtonDownListeners.erase(std::find(leftMouseButtonDownListeners.begin(), leftMouseButtonDownListeners.end(), listener));
}

void InputHandler::DeregisterLeftMouseButtonUpListener(ILeftMouseButtonUpListener* listener)
{
	leftMouseButtonUpListeners.erase(std::find(leftMouseButtonUpListeners.begin(), leftMouseButtonUpListeners.end(), listener));

}

void InputHandler::DeregisterRightMouseButtonDownListener(IRightMouseButtonDownListener* listener)
{
	rightMouseButtonDownListeners.erase(std::find(rightMouseButtonDownListeners.begin(), rightMouseButtonDownListeners.end(), listener));

}

void InputHandler::DeregisterRightMouseButtonUpListener(IRightMouseButtonUpListener* listener)
{
	rightMouseButtonUpListeners.erase(std::find(rightMouseButtonUpListeners.begin(), rightMouseButtonUpListeners.end(), listener));

}

void InputHandler::DeregisterMiddleMouseButtonDownListener(IMiddleMouseButtonDownListener* listener)
{
	middleMouseButtonDownListeners.erase(std::find(middleMouseButtonDownListeners.begin(), middleMouseButtonDownListeners.end(), listener));
}

void InputHandler::DeregisterMiddleMouseButtonUpListener(IMiddleMouseButtonUpListener* listener)
{
	middleMouseButtonUpListeners.erase(std::find(middleMouseButtonUpListeners.begin(), middleMouseButtonUpListeners.end(), listener));
}

void InputHandler::DeregisterMouseWheelUpdateListener(IMouseWheelUpdateListener* listener)
{
	mouseWheelUpdateListeners.erase(std::find(mouseWheelUpdateListeners.begin(), mouseWheelUpdateListeners.end(), listener));
}

Float2 InputHandler::GetMousePosition()
{
	return mousePosition;
}

#pragma endregion