#pragma once
class IAnyKeyDownListener;
class IAnyKeyUpListener;
class IMouseListener;
#include "Scene.h"
#include "IAnyKeyDownListener.h"
#include "IAnyKeyUpListener.h"
#include "IMouseListener.h"
class InputHandler : public IAnyKeyDownListener, public IAnyKeyUpListener, public IMouseListener
{
	InputHandler(Scene* scene);

	// Inherited via IKeyDownListener
	virtual void OnKeyDown(int) override;

	// Inherited via IKeyUpListener
	virtual void OnKeyUp(int) override;

	// Inherited via IMouseListener
	virtual void OnMouseUpdate(int, int, int, int, int, int) override;

};

