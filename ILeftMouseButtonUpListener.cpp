#include "ILeftMouseButtonUpListener.h"

ILeftMouseButtonUpListener::ILeftMouseButtonUpListener(InputHandler* input)
{
	this->input = input;
	input->RegisterLeftMouseButtonUpListener(this);
}

ILeftMouseButtonUpListener::~ILeftMouseButtonUpListener()
{
	input->DeregisterLeftMouseButtonUpListener(this);
}
