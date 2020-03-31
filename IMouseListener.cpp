#include "IMouseListener.h"
IMouseListener::IMouseListener(Scene* scene)
{
	scene->RegisterToOnMouseUpdateCallback(this);
}
