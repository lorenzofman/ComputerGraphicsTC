#pragma once

#include "Types.h"
#include "IRenderable.h"
#include "Float2.h"
#include "RGBFloat.h"
#include "Button.h"
#include "InputHandler.h"
struct Image : public IRenderable, public Button, public IAnyKeyUpListener, public IMouseListener
{
	enum class InterfaceTransformation{None, Translating, Rotating, Scaling};
	RGBFloat* pixels;
	int sizeInBytes;
	int size;
	int width;
	int height;
	bool active;
	InputHandler* input;
	InterfaceTransformation currentTransformation;

	Image(RGBFloat* pixels, int width, int height, Scene *scene, InputHandler* input);

	~Image();

	void ApplyInterfaceTransfomation();

	void Render();

	void SetPosition(Float2 pos);
	void SetScale(double scale);
	void SetRotation(double rotation);

	void Translate(Float2 pos);
	void Rotate(double rot);

	Float2 GetPosition();
	double GetScale();
	double GetRotation();

	void RecalculateButtonRect();

	void Show();
	void Hide();

	
	void CopyTransformFrom(Image* from);

	private:
	Float2 position;
	double scale;
	double rotation;
	Float2 lastMousePosition;

	// Inherited from Button
	void OnButtonDown() override;
	void OnButtonUp() override;

	// Inherited via IAnyKeyUpListener
	virtual void OnKeyUp(int) override;

	// Inherited via IMouseListener
	virtual void OnMouseUpdate(int, int, int, int, int, int) override;

};