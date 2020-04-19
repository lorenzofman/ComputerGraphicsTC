#pragma once

#include <map>

#include "../Primitives/RGBAFloat.h"
#include "../Primitives/Float2.h"
#include "../Primitives/Constants.h"
#include "../Interfaces/IRenderable.h"
#include "../Helpers/Callback.h"
#include "../Canvas2D/Canvas2DExtensions.h"
#include "../UI/Button.h"

class ColorPalette : public IRenderable
{
	public:
	ColorPalette(Float2 buttonPosition);
	Callback<RGBAFloat> colorUpdateCallback;

	virtual void Render() override;
	void OnOpenPalette();
	void ClosePalette();

	void OnColorClick(Button*);
	RGBAFloat GetCurrentColor();
	bool IsMouseOver();

	private:
	void CreateButtons();
	Rect CalculateRectangle(int, int);
	
	std::map<Button*, RGBAFloat> buttons;
	Button* colorButton;
	bool open;
	Float2 position;
};