#pragma once

#include "ImageFilter.h"
#include "Scene.h"
#include "Channel.h"
class ExtractChannel
{
	public:
	static Image* Extract(Channel, Image*, Scene*);
};

