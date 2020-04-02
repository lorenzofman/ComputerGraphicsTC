#include "IRenderable.h"

IRenderable::IRenderable(Scene* scene)
{
	this->scene = scene;
	scene->RegisterToOnRenderCallback(this);
}

IRenderable::~IRenderable()
{
	scene->DeRegisterToOnRenderCallback(this);
}
