#include "IAnyKeyDownListener.h"

IAnyKeyDownListener::IAnyKeyDownListener(Scene* scene)
{
	scene->RegisterToOnKeyDownCallback(this);
	this->scene = scene;
}

IAnyKeyDownListener::~IAnyKeyDownListener()
{
	scene->DeregisterToOnKeyDownCallback(this);
}
