#include "ExtractChannel.h"

void ExtractChannel::Extract(Channel channel, Image* src)
{
	int offset = (int)channel;
	for (int i = 0; i < src->size; i++)
	{
		float val = ((float*)&src->pixels[i])[offset];
		src->pixels[i] = RGBFloat();
		((float*)&src->pixels[i])[offset] = val;
	}
}
