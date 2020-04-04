#pragma once
#include "Scene.h"
#include "InputHandler.h"
#include "InterfaceButton.h"
#include "Image.h"
#include "Rect.h"
#include "Int2.h"
class ImageActions
{
	public:

	static void Init(Scene* sc, InputHandler* in, Image* img);
	static void Display(Int2 position);
	static void Hide();
	static void OnExtractRedButtonClick();
	static void OnExtractGreenButtonClick();
	static void OnExtractBlueButtonClick();
	static void OnConvertToGrayscaleButton();
	static void OnPlotRedHistogramButton();
	static void OnPlotGreenHistogramButton();
	static void OnPlotBlueHistogramButton();
	static void OnPlotLuminescenceHistogramButton();

	static Rect2D ContainingRect;
	private:
	static bool started;
	static Scene* sc;
	static InputHandler* in;
	static Image* img;
	static InterfaceButton** buttons;
};
