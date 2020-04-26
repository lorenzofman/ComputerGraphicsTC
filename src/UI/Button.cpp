#include "Button.h"

#include <iostream>

Button* Button::PressedButton;

Button::Button(RGBAFloat color, Shape* shape)
{
	EventSystem::LeftMouseButtonDownCallback.Register([this]{ this->OnLeftMouseButtonDown();});
	EventSystem::LeftMouseButtonUpCallback.Register([this] {this->OnLeftMouseButtonUp(); });
	this->shape = shape;
	this->color = color;
	this->drag = false;
	this->updateCallbackId = -1;
	this->active = true;
}

bool Button::IsMouseOver()
{
	return shape->IsPointInside(EventSystem::MousePosition);
}

void Button::OnMousePositionUpdate()
{
	if (active == false)
	{
		return;
	}
	if (drag)
	{
		DragCallback.Invoke(this);
	}
	else 
	{
		totalDelta += EventSystem::MousePositionDelta;
		if (abs(totalDelta.x + totalDelta.y) > DragThreshold)
		{
			drag = true;
			DragCallback.Invoke(this);
		}
	}
}

void Button::OnLeftMouseButtonDown()
{
	if (active == false)
	{
		return;
	}
	if (PressedButton != nullptr)
	{
		return;
	}
	if (shape->IsPointInside(EventSystem::MousePosition) == false)
	{
		return;
	}
	PressedButton = this;
	totalDelta = Int2::Zero;
	updateCallbackId =	EventSystem::MouseMovementCallback.Register([this] {this->OnMousePositionUpdate(); });
}

void Button::OnLeftMouseButtonUp()
{
	if (active == false)
	{
		return;
	}
	if (this != PressedButton)
	{
		return;
	}
	if (drag == false)
	{
		ClickCallback.Invoke(this);
	}
	drag = false;
	PressedButton = nullptr;
	EventSystem::MouseMovementCallback.Deregister(updateCallbackId);
}