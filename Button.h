#pragma once
#include <string>

#include "IRenderable.h"
#include "InputHandler.h"
#include "ILeftMouseButtonUpListener.h"
#include "Rect.h"
#include "RGBFloat.h"
class Button : public ILeftMouseButtonUpListener, public ILeftMouseButtonDownListener
{
	public:
	
	Button(Scene*, InputHandler*);
	
	protected:
	
	virtual void OnButtonDown();
	virtual void OnButtonUp();
	Rect2D rect;
	private:
	RGBFloat color;

	// Inherited via ILeftMouseButtonUpListener
	virtual void OnLeftMouseButtonUp(Float2 pos) override;

	// Inherited via ILeftMouseButtonDownListener
	virtual void OnLeftMouseButtonDown(Float2 pos) override;
};

