#include "Image.h"
#include "Scene.h"
#include "Canvas2DExtensions.h"

Image::Image(byte* data, uint bytesSize, ColorSpace colorSpace, int width, int height, Scene* scene) : IRenderable(scene)
{
	this->data = data;
	this->bytesSize = bytesSize;
	this->colorSpace = colorSpace;
	this->width = width;
	this->height = height;
	this->rotation = 0;
	this->scale = 1;
}

Image::~Image()
{
	delete data;
}

void Image::Render()
{
	Canvas2DExtensions::DrawImage(this);
}