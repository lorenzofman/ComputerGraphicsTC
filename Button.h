#pragma once

#include "IRenderable.h"
#include "Rect.h"
#include "Canvas2D.h"
#include "Callback.h"
#include "EventSystem.h"
#include "Rectangle.h"
#include "RGBAFloat.h"

constexpr int DragThreshold = 2;
constexpr float ButtonMouseOverColorMultiplier = 0.8f;

class Button : public IRenderable
{
	public:
	
	Button(RGBAFloat color, Rect2D rect = Rect2D());

	Callback<Button*> DragCallback;
	Callback<Button*> ClickCallback;

	static Button* PressedButton;
	void OnMousePositionUpdate(Int2 deltaPos);
	
	// Inherited via IRenderable
	virtual void Render() override;
	virtual void MouseOver(RGBAFloat& color);
	Rect2D rect;
	RGBAFloat color;
	bool active;
	private:

	Int2 totalDelta;
	bool drag;
	int updateCallbackId; /* Saved for later callback deregistering*/

	void OnLeftMouseButtonDown(Int2);
	void OnLeftMouseButtonUp(Int2);

};