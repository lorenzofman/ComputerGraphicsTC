#pragma once
#include "IRenderable.h"
#include "InputHandler.h"
#include "ILeftMouseButtonUpListener.h"
#include "Rect.h"
#include "RGBFloat.h"
class Button : public ILeftMouseButtonUpListener, public IRenderable
{
	public:
	
	Button(Scene*, InputHandler*, Rect2D, RGBFloat);
	
	protected:
	
	virtual void OnButtonClicked();

	private:
	Rect2D rect;
	RGBFloat color;

	// Inherited via ILeftMouseButtonUpListener
	virtual void OnLeftMouseButtonUp(Float2 pos) override;

	// Inherited via IRenderable
	virtual void Render() override;
};

