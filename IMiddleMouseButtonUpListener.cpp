#include "IMiddleMouseButtonUpListener.h"

IMiddleMouseButtonUpListener::IMiddleMouseButtonUpListener(InputHandler* input)
{
	this->input = input;
	input->RegisterMiddleMouseButtonUpListener(this);
}

IMiddleMouseButtonUpListener::~IMiddleMouseButtonUpListener()
{
	input->DeregisterMiddleMouseButtonUpListener(this);
}
