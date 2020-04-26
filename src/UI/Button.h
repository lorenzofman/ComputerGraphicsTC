#pragma once

#include "../Interfaces/IRenderable.h"
#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Shape.h"
#include "../Canvas2D/Canvas2D.h"
#include "../Helpers/Callback.h"
#include "../World/EventSystem.h"

constexpr int DragThreshold = 2;
constexpr float ButtonMouseOverColorMultiplier = 0.8f;

class Button
{
	public:
	
	static Button* PressedButton;
	
	Shape* shape;
	RGBAFloat color;
	bool active;
	Callback<Button*> DragCallback;
	Callback<Button*> ClickCallback;

	Button(RGBAFloat color, Shape*);
	
	bool IsMouseOver();

	private:
	
	Int2 totalDelta;
	bool drag;
	int updateCallbackId; /* Saved for later callback deregistering*/

	void OnLeftMouseButtonDown();
	void OnLeftMouseButtonUp();
	void OnMousePositionUpdate();

};