#include "IMiddleMouseButtonDownListener.h"

IMiddleMouseButtonDownListener::IMiddleMouseButtonDownListener(InputHandler* input)
{
	this->input = input;
	input->RegisterMiddleMouseButtonDownListener(this);
}

IMiddleMouseButtonDownListener::~IMiddleMouseButtonDownListener()
{
	input->DeregisterMiddleMouseButtonDownListener(this);
}
