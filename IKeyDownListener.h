#pragma once

class InputHandler;

#include "InputHandler.h"

class IKeyDownListener
{
	public:
	virtual void OnKeyDown() = 0;
	IKeyDownListener(InputHandler* input, int key);
};