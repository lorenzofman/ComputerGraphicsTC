#include "IRenderable.h"

IRenderable::IRenderable(Scene* scene)
{
	scene->RegisterToOnRenderCallback(this);
}
