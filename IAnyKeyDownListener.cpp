#include "IAnyKeyDownListener.h"

IAnyKeyDownListener::IAnyKeyDownListener(Scene* scene)
{
	scene->RegisterToOnKeyDownCallback(this);
}
