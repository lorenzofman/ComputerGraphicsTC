#pragma once
#include "Image.h"

constexpr float RedWeight = 0.3f;
constexpr float GreenWeight = 0.59f;
constexpr float BlueWeight = 0.11f;

class Grayscale
{
	public:
	static void Convert(Image*);
	static float GetLuminescence(RGBFloat* f);
};

