#include "Grayscale.h"
#include "RGBFloat.h"

constexpr float RedWeight = 0.3f;
constexpr float GreenWeight = 0.59f;
constexpr float BlueWeight = 0.11f;

Image* Grayscale::Convert(Image* src, Scene* scene)
{
	RGBFloat* grayscale = new RGBFloat[src->size];
	for (int i = 0; i < src->size; i++) 
	{
		RGBFloat color = src->pixels[i];
		float weightedAverage = (RedWeight * color.r) + (GreenWeight * color.g) + (BlueWeight * color.b);
		grayscale[i].r = grayscale[i].g = grayscale[i].b = weightedAverage;
	}
	Image* dst = new Image(grayscale, src->width, src->height, scene, src->input);
	dst->CopyTransformFrom(src);
	return dst;
}
