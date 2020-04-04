#include "ImageActions.h"
#include "ExtractChannel.h"
#include "Channel.h"
#include "Grayscale.h"
#include "ImageHistogram.h"
int constexpr ButtonsCount = 8;
int constexpr ButtonWidth = 280;
int constexpr ButtonHeight = 32;

const RGBFloat btnColor = RGBFloat(0.55f, 0.8f, 0.4f);
const RGBFloat textColor = RGBFloat(1.f, 1.f, 1.f);

Scene* ImageActions::sc;
InputHandler* ImageActions::in;
Image* ImageActions::img;
bool ImageActions::started = false;
Rect2D ImageActions::ContainingRect;
InterfaceButton** ImageActions::buttons;

void ImageActions::Init(Scene* sc, InputHandler* in, Image* img)
{

	if (started)
	{
		return;
	}
	started = true;

	ImageActions::sc = sc;
	ImageActions::in = in;
	ImageActions::img = img;

	buttons = new InterfaceButton*[ButtonsCount];
	buttons[0] = new InterfaceButton(sc, in, "Extract Red channel", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnExtractRedButtonClick);
	buttons[1] = new InterfaceButton(sc, in, "Extract Green channel", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnExtractGreenButtonClick);
	buttons[2] = new InterfaceButton(sc, in, "Extract Blue channel", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnExtractBlueButtonClick);
	buttons[3] = new InterfaceButton(sc, in, "Convert to Grayscale", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnConvertToGrayscaleButton);
	buttons[4] = new InterfaceButton(sc, in, "Plot Red histogram", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnPlotRedHistogramButton);
	buttons[5] = new InterfaceButton(sc, in, "Plot Green histogram", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnPlotGreenHistogramButton);
	buttons[6] = new InterfaceButton(sc, in, "Plot Blue histogram", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnPlotBlueHistogramButton);
	buttons[7] = new InterfaceButton(sc, in, "Plot Luminescence histogram", btnColor, textColor, Rect2D(0, 0, 0, 0), &OnPlotLuminescenceHistogramButton);
	Hide();
}

void ImageActions::Display(Int2 position)
{
	float x1 = (float) position.x;
	float x2 = x1 + ButtonWidth;
	for (int i = 0; i < ButtonsCount; i++)
	{
		float y2 = (float) position.y - i * ButtonHeight;
		float y1 = y2 - ButtonHeight;
		buttons[i]->rect = Rect2D(x1, y1, x2, y2);
		buttons[i]->visible = true;
	}
	ContainingRect = Rect2D(x1, (float)position.y - (ButtonsCount)*ButtonHeight, x2, (float)position.y);
}

void ImageActions::Hide()
{
	for (int i = 0; i < ButtonsCount; i++)
	{
		buttons[i]->visible = false;
	}
}

void ImageActions::OnExtractRedButtonClick()
{
	ExtractChannel::Extract(Channel::R, img);
	Hide();
}

void ImageActions::OnExtractGreenButtonClick()
{
	ExtractChannel::Extract(Channel::G, img);
	Hide();
}

void ImageActions::OnExtractBlueButtonClick()
{
	ExtractChannel::Extract(Channel::B, img);
	Hide();
}

void ImageActions::OnConvertToGrayscaleButton()
{
	Grayscale::Convert(img);
	Hide();
}

void ImageActions::OnPlotRedHistogramButton()
{
	ImageHistogram(sc, in, img, Rect2D(300,0,600,600), RGBFloat(0.917f, 0.262f, 0.207f), Channel::R);
	Hide();
}

void ImageActions::OnPlotGreenHistogramButton()
{
	ImageHistogram(sc, in, img, Rect2D(300, 0, 600, 600), RGBFloat(0.203f, 0.658f, 0.325f), Channel::G);
	Hide();
}

void ImageActions::OnPlotBlueHistogramButton()
{
	ImageHistogram(sc, in, img, Rect2D(300, 0, 600, 600), RGBFloat(0.258f, 0.521f, 0.956f), Channel::B);
	Hide();
}

void ImageActions::OnPlotLuminescenceHistogramButton()
{
	ImageHistogram(sc, in, img, Rect2D(300, 0, 600, 600), RGBFloat(0.396f, 0.396f, 0.396f), Channel::None);
	Hide();
}
