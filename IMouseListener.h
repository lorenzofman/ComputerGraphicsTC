#pragma once
class Scene;
#include "Scene.h"
class IMouseListener
{
	public:
	virtual void OnMouseUpdate(int, int, int, int, int, int) = 0;
	IMouseListener(Scene* scene);
};