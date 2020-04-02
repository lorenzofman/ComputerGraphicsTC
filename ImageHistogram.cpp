#include "ImageHistogram.h"
#include "Canvas2D.h"
void ImageHistogram::Render()
{
	Canvas2D::SetColor(color.r, color.g, color.b);
	float width = drawingArea.TopRight.x - drawingArea.BottomLeft.x;
	float height = drawingArea.TopRight.y - drawingArea.BottomLeft.y;
	float xFrac = width / 256;
	float yFrac = height / max;
	int val;
	for (int i = 0; i < 256; i++)
	{
		if ((val = values[i]) == 0)
		{
			continue;
		}
		Canvas2D::DrawFilledRect((int) (xFrac * i), 0, (int) (xFrac * (i + 1)), int(yFrac * val));
	}
}
/* If no channel is passed as parameter, histogram assumes image is grayscaled and pick the first channel (Red)*/
ImageHistogram::ImageHistogram(Scene* sc, Image* image, Rect2D drawingArea, RGBFloat barsColor, Channel channel) : IRenderable(sc)
{
	values = new int[256];
	memset(values, 0, sizeof(int) * 256);

	this->color = barsColor;

	this->drawingArea = drawingArea;

	int ch = (int)channel;
	max = 0;
	for (int i = 0; i < image->size; i++)
	{
		float intensity = ((float*)&image->pixels[i])[ch]; // Access channel value
		int value = (int) (intensity * 255);
		values[value]++;
		if (values[value] > max)
		{
			max = values[value];
		}
	}
}
