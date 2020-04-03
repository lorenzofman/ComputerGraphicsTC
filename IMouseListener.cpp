#include "IMouseListener.h"
IMouseListener::IMouseListener(Scene* scene)
{
	this->scene = scene;
	scene->RegisterToOnMouseUpdateCallback(this);
}

IMouseListener::~IMouseListener()
{
	scene->DeregisterToOnMouseUpdateCallback(this);
}

