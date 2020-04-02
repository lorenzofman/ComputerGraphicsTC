#include "IRightMouseButtonDownListener.h"

IRightMouseButtonDownListener::IRightMouseButtonDownListener(InputHandler* input)
{
	this->input = input;
	input->RegisterRightMouseButtonDownListener(this);
}

IRightMouseButtonDownListener::~IRightMouseButtonDownListener()
{
	input->DeregisterRightMouseButtonDownListener(this);
}
