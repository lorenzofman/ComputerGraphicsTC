#include "IAnyKeyUpListener.h"

IAnyKeyUpListener::IAnyKeyUpListener(Scene* scene)
{
	scene->RegisterToOnKeyUpCallback(this);
}
