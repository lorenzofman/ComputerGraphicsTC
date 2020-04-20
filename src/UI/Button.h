#pragma once

#include "../Interfaces/IRenderable.h"
#include "../Primitives/Rect.h"
#include "../Primitives/RGBAFloat.h"
#include "../Canvas2D/Canvas2D.h"
#include "../Helpers/Callback.h"
#include "../World/EventSystem.h"
#include "../Shapes/Rectangle.h"

constexpr int DragThreshold = 2;
constexpr float ButtonMouseOverColorMultiplier = 0.8f;

class Button : public IRenderable
{
	public:
	
	Button(RGBAFloat color, Rect rect = Rect());

	Callback<Button*> DragCallback;
	Callback<Button*> ClickCallback;

	static Button* PressedButton;
	void OnMousePositionUpdate();
	
	// Inherited via IRenderable
	virtual void Render() override;
	virtual void MouseOver(RGBAFloat& color);
	Rect rect;
	RGBAFloat color;
	bool active;
	private:

	Int2 totalDelta;
	bool drag;
	int updateCallbackId; /* Saved for later callback deregistering*/

	void OnLeftMouseButtonDown();
	void OnLeftMouseButtonUp();

};