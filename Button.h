#pragma once

#include "IRenderable.h"
#include "Rect.h"
#include "Canvas2D.h"
#include "Callback.h"
#include "EventSystem.h"
#include "Rectangle.h"

constexpr int DragThreshold = 5;

class Button : public IRenderable
{
	public:
	
	Button(Rect2D rect = Rect2D());

	Callback<Int2> DragCallback;
	Callback<Int2> ClickCallback;

	static Button* PressedButton;
	void OnMousePositionUpdate(Int2 deltaPos);
	
	// Inherited via IRenderable
	virtual void Render() override;
	Rect2D rect;
	
	private:

	Int2 totalDelta;
	bool drag;
	int updateCallbackId; /* Saved for later callback deregistering*/

	void OnLeftMouseButtonDown(Int2);
	void OnLeftMouseButtonUp(Int2);

};