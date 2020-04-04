#pragma once
#include <string>
#include "Scene.h"
#include "Button.h"
#include "RGBFloat.h"
class InterfaceButton : public Button, IRenderable
{
	public: 
	InterfaceButton(Scene*, InputHandler*, const char* title, RGBFloat buttonColor, RGBFloat textColor, Rect2D rect, void(*OnClick)());
	bool interactable;
	bool visible;
	protected:
	// Inherited via IRenderable
	virtual void Render() override;

	// Inherited via Button
	virtual void OnButtonDown() override;
	InputHandler* in;
	const char* title;
	int titleLength;
	RGBFloat buttonColor;
	RGBFloat textColor;
	void(*OnClick)();
};