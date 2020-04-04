#include "ImageHistogram.h"
#include "Canvas2D.h"
#include "Grayscale.h"
extern int ScreenWidth;
extern int ScreenHeight;
void ImageHistogram::Render()
{
	Canvas2D::ClearScreen(0,0,0);
	Canvas2D::SetColor(color.r, color.g, color.b);
	int yOffset = ScreenHeight / 8;
	int xOffset = ScreenWidth / 8;
	drawingArea = Rect2D(xOffset, yOffset, ScreenWidth - xOffset, ScreenHeight - yOffset);
	float initialX = drawingArea.BottomLeft.x;
	float initialY = drawingArea.BottomLeft.y;
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
		float x1 = xFrac * i + initialX;
		float x2 = xFrac * (i + 1) + initialX;
		float y1 = initialY;
		float y2 = int(yFrac * val) + initialY;
		Canvas2D::DrawFilledRect((int) x1, (int) y1, (int) x2, (int) y2);
	}
}
float GetChannelIntensitty(Image* image, int i, int ch)
{
	return ((float*)&image->pixels[i])[ch];
}

float GetGrayIntensity(Image* img, int i)
{
	return Grayscale::GetLuminescence(&img->pixels[i]);
}

ImageHistogram::ImageHistogram(Scene* sc, InputHandler* in, Image* image, Rect2D drawingArea, RGBFloat barsColor, Channel channel) : IRenderable(sc), IKeyUpListener(in, 27)
{
	values = new int[256];
	memset(values, 0, sizeof(int) * 256);

	this->color = barsColor;

	this->drawingArea = drawingArea;

	int ch = (int)channel;
	max = 0;
	for (int i = 0; i < image->size; i++)
	{
		float intensity = (channel == Channel::None) ? GetGrayIntensity(image, i) : GetChannelIntensitty(image, i, ch);
		int value = (int) (intensity * 255);
		values[value]++;
		if (values[value] > max)
		{
			max = values[value];
		}
	}
}

ImageHistogram::~ImageHistogram()
{
	delete[] values;
}

// Escape suicide
void ImageHistogram::OnKeyUp()
{
	delete this;
}
