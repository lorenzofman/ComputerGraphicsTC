#pragma once
#include "InputHandler.h"
#include "Float2.h"
class IRightMouseButtonUpListener
{
	public:
	virtual void OnRightMouseButtonUp(Float2 pos) = 0;
	IRightMouseButtonUpListener(InputHandler* input);
};