#pragma once
class InputHandler;

#include "InputHandler.h"

class IKeyUpListener
{
	public:
	virtual void OnKeyUp() = 0;
	IKeyUpListener(InputHandler* input, int key);
};