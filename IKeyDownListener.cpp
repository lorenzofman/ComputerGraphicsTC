#include "IKeyDownListener.h"

IKeyDownListener::IKeyDownListener(InputHandler* input, int key)
{
	input->RegisterOnKeyDown(key, this);
}
