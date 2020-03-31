#pragma once
#include "InputHandler.h"
#include "Float2.h"
class IMiddleMouseButtonUpListener
{
	public:
	virtual void OnMiddleMouseButtonUp(Float2 pos) = 0;
	IMiddleMouseButtonUpListener(InputHandler* input);
};
