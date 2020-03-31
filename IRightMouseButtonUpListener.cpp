#include "IRightMouseButtonUpListener.h"

IRightMouseButtonUpListener::IRightMouseButtonUpListener(InputHandler* input)
{
	input->RegisterRightMouseButtonUpListener(this);
}
