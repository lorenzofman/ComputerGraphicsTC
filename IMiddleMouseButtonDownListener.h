#pragma once
#include "InputHandler.h"
#include "Float2.h"
class IMiddleMouseButtonDownListener
{
	public:
	virtual void OnMiddleMouseButtonDown(Float2 pos) = 0;
	IMiddleMouseButtonDownListener(InputHandler* input);
};