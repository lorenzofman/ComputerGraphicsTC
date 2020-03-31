#include "ColorConversions.h"

RGB24 ColorConversions::RGBFloatToRGB24(RGBFloat rgbf)
{
	return RGB24((byte) rgbf.r * 255, (byte) rgbf.g * 255, (byte) rgbf.b * 255);
}

BGR24 ColorConversions::RGB24ToBGR24(RGB24 rgb)
{
	return BGR24(rgb.b, rgb.g, rgb.r);
}

RGB24 ColorConversions::BGR24ToRGB24(BGR24 bgr)
{
	return RGB24(bgr.r, bgr.g, bgr.b);
}

RGBFloat ColorConversions::RGB24ToRGBFloat(RGB24 rgb)
{
	return RGBFloat(rgb.r / 255.f, rgb.g / 255.f, rgb.b / 255.f);
}
