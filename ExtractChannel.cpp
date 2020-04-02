#include "ExtractChannel.h"

Image* ExtractChannel::Extract(Channel channel, Image* src, Scene* sc)
{
	int offset = (int)channel;
	RGBFloat* arr = new RGBFloat[src->size];
	for (int i = 0; i < src->size; i++)
	{
		arr[i] = RGBFloat();
		float val = ((float*)&src->pixels[i])[offset];
		((float*)&arr[i])[offset] = val;
	}
	Image* dst = new Image(arr, src->width, src->height, sc, src->input);
	dst->CopyTransformFrom(src);
	return dst;
}
