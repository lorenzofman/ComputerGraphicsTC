#include "Button.h"
Button* Button::PressedButton;
Button::Button(Rect2D rect)
{
	EventSystem::LeftMouseButtonDownCallback.Register([this](Int2 arg){ this->OnLeftMouseButtonDown(arg);});
	EventSystem::LeftMouseButtonUpCallback.Register([this](Int2 arg) {this->OnLeftMouseButtonUp(arg); });
	this->rect = rect;
	this->drag = false;
	this->updateCallbackId = -1;
}

void Button::OnMousePositionUpdate(Int2 deltaPos)
{
	if (drag)
	{
		DragCallback.Invoke(deltaPos);
	}
	else 
	{
		totalDelta += deltaPos;
		if (abs(totalDelta.x + totalDelta.y) > DragThreshold)
		{
			drag = true;
			DragCallback.Invoke(totalDelta);
		}
	}
}

void Button::OnLeftMouseButtonDown(Int2 pos)
{
	if (PressedButton != nullptr)
	{
		return;
	}
	if (rect.IsPointInside(pos) == false)
	{
		return;
	}
	PressedButton = this;
	totalDelta = Int2::Zero;
	updateCallbackId =	EventSystem::MouseMovementCallback.Register([this] (Int2 mouseDelta) {this->OnMousePositionUpdate(mouseDelta); });
}

void Button::OnLeftMouseButtonUp(Int2 pos)
{
	if (this != PressedButton)
	{
		return;
	}
	if (drag == false)
	{
		ClickCallback.Invoke(pos);
	}
	drag = false;
	PressedButton = nullptr;
	EventSystem::MouseMovementCallback.Deregister(updateCallbackId);
}

void Button::Render()
{
	Canvas2D::DrawFilledRect((int)rect.BottomLeft.x, (int)rect.BottomLeft.y, (int)rect.TopRight.x, (int)rect.TopRight.y);
}