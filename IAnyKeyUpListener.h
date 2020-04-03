#pragma once
class Scene;
#include "Scene.h"
class IAnyKeyUpListener
{
	public:
	virtual void OnKeyUp(int) = 0;
	IAnyKeyUpListener(Scene* scene);
	~IAnyKeyUpListener();

	private:
	Scene* scene;
};