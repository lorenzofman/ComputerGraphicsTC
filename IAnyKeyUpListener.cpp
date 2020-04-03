#include "IAnyKeyUpListener.h"

IAnyKeyUpListener::IAnyKeyUpListener(Scene* scene)
{
	scene->RegisterToOnKeyUpCallback(this);
	this->scene = scene;
}

IAnyKeyUpListener::~IAnyKeyUpListener()
{
	scene->DeregisterToOnKeyUpCallback(this);
}
