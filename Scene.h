#pragma once
class IRenderable;
class IAnyKeyDownListener;
class IAnyKeyUpListener;
class IMouseListener;
#include <vector>

#include "IRenderable.h"
#include "IAnyKeyDownListener.h"
#include "IAnyKeyUpListener.h"
#include "IMouseListener.h"
class Scene
{
	public: 
	
	void OnRender();
	void OnKeyDownCallback(int);
	void OnKeyUpCallback(int);
	void OnMouseUpdateCallback(int, int, int, int, int, int);
	
	void RegisterToOnRenderCallback(IRenderable* renderable);
	void RegisterToOnKeyDownCallback(IAnyKeyDownListener* keyDownListener);
	void RegisterToOnKeyUpCallback(IAnyKeyUpListener* keyUpListener);
	void RegisterToOnMouseUpdateCallback(IMouseListener* mouseListener);

	private:
	std::vector<IRenderable*> renderableObjects = std::vector<IRenderable*>();
	std::vector<IAnyKeyDownListener*> keyDownListeners = std::vector<IAnyKeyDownListener*>();
	std::vector<IAnyKeyUpListener*> keyUpListeners = std::vector<IAnyKeyUpListener*>();
	std::vector<IMouseListener*> mouseListeners = std::vector<IMouseListener*>();
};

