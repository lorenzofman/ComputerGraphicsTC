#pragma once
class Scene;
#include "Scene.h"
class IAnyKeyDownListener
{
	public:
	virtual void OnKeyDown(int) = 0;
	IAnyKeyDownListener(Scene* scene);
};