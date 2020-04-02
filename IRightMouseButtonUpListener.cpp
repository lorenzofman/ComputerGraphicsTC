#include "IRightMouseButtonUpListener.h"

IRightMouseButtonUpListener::IRightMouseButtonUpListener(InputHandler* input)
{
	this->input = input;
	input->RegisterRightMouseButtonUpListener(this);
}

IRightMouseButtonUpListener::~IRightMouseButtonUpListener()
{
	input->DeregisterRightMouseButtonUpListener(this);
}
