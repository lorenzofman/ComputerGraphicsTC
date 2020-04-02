#pragma once
#include "InputHandler.h"
#include "Float2.h"
class ILeftMouseButtonDownListener
{
	public:
	virtual void OnLeftMouseButtonDown(Float2 pos) = 0;
	ILeftMouseButtonDownListener(InputHandler* input);
	~ILeftMouseButtonDownListener();
	InputHandler* input;
};