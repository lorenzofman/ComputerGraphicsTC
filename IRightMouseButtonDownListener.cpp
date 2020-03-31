#include "IRightMouseButtonDownListener.h"

IRightMouseButtonDownListener::IRightMouseButtonDownListener(InputHandler* input)
{
	input->RegisterRightMouseButtonDownListener(this);
}
