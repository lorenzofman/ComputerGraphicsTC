#pragma once

#include <map>

#include "IRenderable.h"
#include "Callback.h"
#include "RGBAFloat.h"
#include "Float2.h"
#include "Canvas2DExtensions.h"
#include "Constants.h"
#include "Button.h"
class ColorPalette : public IRenderable
{
	public:
	ColorPalette(Float2 buttonPosition);
	Callback<RGBAFloat> colorUpdateCallback;

	virtual void Render() override;
	void OnOpenPalette();
	void OnColorClick(Button*);


	private:
	void CreateButtons();
	Rect2D CalculateRectangle(int, int);
	std::map<Button*, RGBAFloat> buttons;
	Button* colorButton;

	Float2 position;
};