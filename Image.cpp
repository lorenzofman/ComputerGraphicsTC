#include <iostream>
#include <cmath>

#include "Image.h"
#include "Scene.h"
#include "Canvas2DExtensions.h"
#include "ImageActions.h"

Image::Image(RGBFloat* pixels, int width, int height, Scene* scene, InputHandler* input) :
	IRenderable(scene),
	Button(scene, input),
	IAnyKeyUpListener(scene),
	IRightMouseButtonUpListener(input)
{
	this->pixels = pixels;
	this->width = width;
	this->height = height;
	this->size = width * height;
	this->rotation = 0;
	this->scale = 1;
	this->input = input;
	active = true;

	currentTransformation = InterfaceTransformation::None;
	lastMousePosition = Float2();

	RecalculateButtonRect();

	ImageActions::Init(scene, input, this);
}

Image::~Image()
{
	delete pixels;
}

void Image::ApplyInterfaceTransfomation()
{
	switch (currentTransformation)
	{
		case InterfaceTransformation::Translating:
		{
			Float2 translationDelta = input->GetMousePosition() - lastMousePosition;
			Translate(translationDelta);
			break;
		}
		case InterfaceTransformation::Rotating:
		{
			Float2 dif = input->GetMousePosition() - position;
			Float2 previousDif = lastMousePosition - position;
			double angleToCenter = atan2f(dif.x, dif.y);
			double previousAngleToCenter = atan2f(previousDif.x, previousDif.y);
			double rotationDelta = previousAngleToCenter - angleToCenter;
			Rotate(rotationDelta);
			break;
		}
		case InterfaceTransformation::Scaling:
		{
			float distance = Float2::Distance(input->GetMousePosition(), position);
			float previousDistance = Float2::Distance(lastMousePosition, position);
			float scaleDelta = distance / previousDistance;
			SetScale(scale * scaleDelta);
			break;
		}
		default:
			break;
	}
	lastMousePosition = input->GetMousePosition();
}

void Image::Render()
{
	if (active)
	{
		Canvas2DExtensions::DrawImage(this);
		ApplyInterfaceTransfomation();
	}
}

void Image::SetPosition(Float2 position)
{
	this->position = position;
	RecalculateButtonRect();
}

void Image::SetScale(double scale)
{
	this->scale = scale;
	RecalculateButtonRect();
}

void Image::SetRotation(double rotation)
{
	this->rotation = rotation;
	RecalculateButtonRect();
}

void Image::Translate(Float2 pos)
{
	SetPosition(position + pos);
}

void Image::Rotate(double rot)
{
	SetRotation (rotation + rot);
}

Float2 Image::GetPosition()
{
	return position;
}

double Image::GetScale()
{
	return scale;
}

double Image::GetRotation()
{
	return rotation;
}

void Image::RecalculateButtonRect()
{
	rect = Rect2D(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);
	rect.Rotate(rotation);
	rect.Scale(scale);
	rect.Translate(position);
}

void Image::Show()
{
	this->active = true;
}

void Image::Hide()
{
	this->active = false;
}

void Image::OnButtonDown()
{
	if (currentTransformation == InterfaceTransformation::None)
	{
		currentTransformation = InterfaceTransformation::Translating;
	}
	else
	{
		currentTransformation = InterfaceTransformation::None;
	}
}

void Image::OnLeftMouseButtonUp(Float2 pos)
{
	Button::OnLeftMouseButtonUp(pos);
	currentTransformation = InterfaceTransformation::None;
}

void Image::OnLeftMouseButtonDown(Float2 pos)
{
	Button::OnLeftMouseButtonDown(pos);
	if (ImageActions::ContainingRect.IsPointInside(pos) == false)
	{
		ImageActions::Hide();
	}
}

void Image::CopyTransformFrom(Image* from)
{
	this->position = from->position;
	this->rotation = from->rotation;
	this->scale = from->scale;
}

void Image::OnKeyUp(int key)
{
	if (key == 13)
	{
		currentTransformation = InterfaceTransformation::None;
		return;
	}
	if (currentTransformation == InterfaceTransformation::None)
	{
		switch (key)
		{
			case 'g':
				currentTransformation = InterfaceTransformation::Translating;
				break;
			case 's':
				currentTransformation = InterfaceTransformation::Scaling;
				break;
			case 'r':
				currentTransformation = InterfaceTransformation::Rotating;
				break;
		}
	}
}

void Image::OnRightMouseButtonUp(Float2 pos)
{
	if (rect.IsPointInside(pos) == false)
	{
		return;
	}

	ImageActions::Display(Int2(pos));
}
