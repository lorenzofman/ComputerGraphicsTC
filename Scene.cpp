#include <algorithm>

#include "Scene.h"
#include "Canvas2D.h"
#include "Types.h"
void Scene::OnRender()
{
	Canvas2D::ClearScreen(0.15f, 0.15f, 0.15f);
	for (uint  i = 0; i < renderableObjects.size(); i++)
	{
		renderableObjects[i]->Render();
	}
}

void Scene::OnKeyDownCallback(int key)
{
	for (uint i = 0; i < keyDownListeners.size(); i++)
	{
		keyDownListeners[i]->OnKeyDown(key);
	}
}

void Scene::OnKeyUpCallback(int key)
{
	for (uint i = 0; i < keyUpListeners.size(); i++)
	{
		keyUpListeners[i]->OnKeyUp(key);
	}
}

void Scene::OnMouseUpdateCallback(int button, int state, int wheel, int direction, int x, int y)
{
	for (uint i = 0; i < mouseListeners.size(); i++)
	{
		mouseListeners[i]->OnMouseUpdate(button, state, wheel, direction, x, y);
	}
}

void Scene::RegisterToOnRenderCallback(IRenderable* renderable)
{
	renderableObjects.push_back(renderable);
}

void Scene::RegisterToOnKeyDownCallback(IAnyKeyDownListener* keyDownListener)
{
	keyDownListeners.push_back(keyDownListener);
}

void Scene::RegisterToOnKeyUpCallback(IAnyKeyUpListener* keyUpListener)
{
	keyUpListeners.push_back(keyUpListener);
}

void Scene::RegisterToOnMouseUpdateCallback(IMouseListener* mouseListener)
{
	mouseListeners.push_back(mouseListener);
}

void Scene::DeregisterToOnRenderCallback(IRenderable* renderable)
{
	auto at = std::find(renderableObjects.begin(), renderableObjects.end(), renderable);
	renderableObjects.erase(at);
}

void Scene::DeregisterToOnKeyDownCallback(IAnyKeyDownListener* keyDownListener)
{
	auto at = std::find(keyDownListeners.begin(), keyDownListeners.end(), keyDownListener);
	keyDownListeners.erase(at);
}

void Scene::DeregisterToOnKeyUpCallback(IAnyKeyUpListener* keyUpListener)
{
	auto at = std::find(keyUpListeners.begin(), keyUpListeners.end(), keyUpListener);
	keyUpListeners.erase(at);
}

void Scene::DeregisterToOnMouseUpdateCallback(IMouseListener* mouseListener)
{
	auto at = std::find(mouseListeners.begin(), mouseListeners.end(), mouseListener);
	mouseListeners.erase(at);
}
