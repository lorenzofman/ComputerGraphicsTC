#include "ILeftMouseButtonDownListener.h"

ILeftMouseButtonDownListener::ILeftMouseButtonDownListener(InputHandler* input)
{
	input->RegisterLeftMouseButtonDownListener(this);
}
