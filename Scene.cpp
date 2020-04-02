#include "Scene.h"
#include "Canvas2D.h"

void Scene::OnRender()
{
	Canvas2D::ClearScreen(0, 0, 0);
	for (auto&& renderable : renderableObjects)
	{
		renderable->Render();
	}
}

void Scene::OnKeyDownCallback(int key)
{
	for (auto&& keyDownListener : keyDownListeners)
	{
		keyDownListener->OnKeyDown(key);
	}
}

void Scene::OnKeyUpCallback(int key)
{
	for (auto&& keyUpListener : keyUpListeners)
	{
		keyUpListener->OnKeyUp(key);
	}
}

void Scene::OnMouseUpdateCallback(int button, int state, int wheel, int direction, int x, int y)
{
	for (auto&& mouseListener : mouseListeners)
	{
		mouseListener->OnMouseUpdate(button, state, wheel, direction, x, y);
	}
}

void Scene::RegisterToOnRenderCallback(IRenderable* renderable)
{
	renderableObjects.push_back(renderable);
}

void Scene::DeRegisterToOnRenderCallback(IRenderable* renderable)
{
	auto at = std::find(renderableObjects.begin(), renderableObjects.end(), renderable);
	renderableObjects.erase(at);
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
