#include "Button.h"
#include <iostream>
Button* Button::PressedButton;
Button::Button(RGBAFloat color, Rect rect)
{
	EventSystem::LeftMouseButtonDownCallback.Register([this]{ this->OnLeftMouseButtonDown();});
	EventSystem::LeftMouseButtonUpCallback.Register([this] {this->OnLeftMouseButtonUp(); });
	this->rect = rect;
	this->color = color;
	this->drag = false;
	this->updateCallbackId = -1;
	this->active = true;
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
	if (rect.IsPointInside(EventSystem::MousePosition) == false)
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

void Button::Render()
{
	if (active == false)
	{
		return;
	}
	RGBAFloat color = this->color;
	bool mouseHover = rect.IsPointInside(EventSystem::MousePosition);
	if (mouseHover)
	{
		MouseOver(color);
	}
	Canvas2D::SetColor(color);
	Canvas2D::DrawFilledRect((int)rect.BottomLeft.x, (int)rect.BottomLeft.y, (int)rect.TopRight.x, (int)rect.TopRight.y);
}

void Button::MouseOver(RGBAFloat& color)
{
	color *= ButtonMouseOverColorMultiplier;
}
