#include "ILeftMouseButtonUpListener.h"

ILeftMouseButtonUpListener::ILeftMouseButtonUpListener(InputHandler* input)
{
	input->RegisterLeftMouseButtonUpListener(this);
}
