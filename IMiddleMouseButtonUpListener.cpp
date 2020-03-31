#include "IMiddleMouseButtonUpListener.h"

IMiddleMouseButtonUpListener::IMiddleMouseButtonUpListener(InputHandler* input)
{
	input->RegisterMiddleMouseButtonUpListener(this);
}
