#include "Grayscale.h"
#include "RGBFloat.h"

void Grayscale::Convert(Image* src)
{
	for (int i = 0; i < src->size; i++) 
	{
		float weightedAverage = GetLuminescence(&src->pixels[i]);
		src->pixels[i].r = src->pixels[i].g = src->pixels[i].b = weightedAverage;
	}
}

float Grayscale::GetLuminescence(RGBFloat* f)
{
	return f->r * RedWeight + f->g * GreenWeight + f->b * BlueWeight;
}
