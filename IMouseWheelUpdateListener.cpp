#include "IMouseWheelUpdateListener.h"

IMouseWheelUpdateListener::IMouseWheelUpdateListener(InputHandler* input)
{
	input->RegisterMouseWheelUpdateListener(this);
}
