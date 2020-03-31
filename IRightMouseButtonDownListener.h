#pragma once
#include "InputHandler.h"
#include "Float2.h"
class IRightMouseButtonDownListener
{
	public:
	virtual void OnRightMouseButtonDown(Float2 pos) = 0;
	IRightMouseButtonDownListener(InputHandler* input);
};