#include "IKeyUpListener.h"

IKeyUpListener::IKeyUpListener(InputHandler* input, int key)
{
	input->RegisterOnKeyUp(key, this);
}
