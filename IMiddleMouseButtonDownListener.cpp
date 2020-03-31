#include "IMiddleMouseButtonDownListener.h"

IMiddleMouseButtonDownListener::IMiddleMouseButtonDownListener(InputHandler* input)
{
	input->RegisterMiddleMouseButtonDownListener(this);
}
