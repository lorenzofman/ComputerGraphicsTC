#include "IMouseWheelUpdateListener.h"

IMouseWheelUpdateListener::IMouseWheelUpdateListener(InputHandler* input)
{
	this->input = input;
	input->RegisterMouseWheelUpdateListener(this);
}

IMouseWheelUpdateListener::~IMouseWheelUpdateListener()
{
	input->DeregisterMouseWheelUpdateListener(this);
}
