#pragma once
class InputHandler;
enum class MouseWheelDirection;
#include "InputHandler.h"
class IMouseWheelUpdateListener
{
	public:
	virtual void OnMouseWheelUpdate(MouseWheelDirection dir) = 0;
	IMouseWheelUpdateListener(InputHandler* input);
};