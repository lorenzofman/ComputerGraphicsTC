#include "Grayscale.h"
#include "RGBFloat.h"

constexpr float RedWeight = 0.3f;
constexpr float GreenWeight = 0.59f;
constexpr float BlueWeight = 0.11f;

void Grayscale::Convert(Image* src)
{
	for (int i = 0; i < src->size; i++) 
	{
		RGBFloat color = src->pixels[i];
		float weightedAverage = (RedWeight * color.r) + (GreenWeight * color.g) + (BlueWeight * color.b);
		src->pixels[i].r = src->pixels[i].g = src->pixels[i].b = weightedAverage;
	}
}