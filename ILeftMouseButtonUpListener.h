#pragma once
#include "InputHandler.h"
#include "Float2.h"
class ILeftMouseButtonUpListener
{
	public:
	virtual void OnLeftMouseButtonUp(Float2 pos) = 0;
	ILeftMouseButtonUpListener(InputHandler* input);
};