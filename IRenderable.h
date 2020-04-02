#pragma once
class Scene;
#include "Scene.h"
class IRenderable
{
	public:
		virtual void Render() = 0;
		IRenderable (Scene* scene);
		~IRenderable();
	private:
	Scene *scene;
};