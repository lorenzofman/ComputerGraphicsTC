#include "ILeftMouseButtonDownListener.h"

ILeftMouseButtonDownListener::ILeftMouseButtonDownListener(InputHandler* input)
{
	this->input = input;
	input->RegisterLeftMouseButtonDownListener(this);
}

ILeftMouseButtonDownListener::~ILeftMouseButtonDownListener()
{
	input->DeregisterLeftMouseButtonDownListener(this);
}
