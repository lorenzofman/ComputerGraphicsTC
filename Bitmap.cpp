#include <fstream>
#include <iostream>
#include "Bitmap.h"
#include "Image.h"
#include "RGBFloat.h"
void Bitmap::ReadHeader(std::ifstream*& stream, BitmapHeader*& bmpHeader)
{
	stream->read((char*)bmpHeader, sizeof(BitmapHeader));
}

/*https://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2*/
bool IsPot(int v)
{
	return v && !(v & (v - 1));
}
void ValidateFile(BitmapHeader* bmpHeader)
{
	try 
	{
		if (bmpHeader->type != MagicIdentifier)
		{
			throw "Invalid BMP file";
		}

		if (bmpHeader->compression != 0)
		{
			throw "Compressed BMP read is not supported yet";
		}

		if (bmpHeader->bits != 24)
		{
			throw "Non BGR BMP is not supported yet";
		}

		if (bmpHeader->planes != 1)
		{
			throw "Number of planes is not supported yet";
		}
		if (IsPot(bmpHeader->height) == false || IsPot(bmpHeader->width) == false)
		{
			printf("Warning: BMP file is Not a Power Of Two (NPOT)\n");
		}
	}
	catch (const std::exception & ex) 
	{
		std::cerr << ex.what() << std::endl;
		throw ex;
	}
	
}

byte* Bitmap::ReadData(std::ifstream*& stream, BitmapHeader*& bmpHeader)
{
	int size = bmpHeader->width * bmpHeader->height * 3;
	byte* data = new byte[bmpHeader->width * bmpHeader->height * 3];
	stream->read((char*)data, size);
	return data;
}
RGBFloat* ConvertBGR24ToRGBFloat(byte* arr, int size)
{
	RGBFloat* buffer = new RGBFloat[size];
	for (int i = 0; i < size; i++)
	{
		float b = arr[i * 3 + 0] / 255.0f;
		float g = arr[i * 3 + 1] / 255.0f;
		float r = arr[i * 3 + 2] / 255.0f;
		buffer[i] = RGBFloat(r, g, b);
	}
	return buffer;
}
Image* Bitmap::Read(std::ifstream* stream, Scene* scene, InputHandler* input)
{
	BitmapHeader* bmpHeader = new BitmapHeader();
	ReadHeader(stream, bmpHeader);
	ValidateFile(bmpHeader);
	byte* data = ReadData(stream, bmpHeader);
	RGBFloat* fData = ConvertBGR24ToRGBFloat(data, bmpHeader->width * bmpHeader->height);
	return new Image(fData, bmpHeader->width, bmpHeader->height, scene, input);
}

void Bitmap::Write(Image* image, std::ofstream* stream)
{
	int w = image->width;
	int h = image->height;
	int size = h * w;
	byte* bgr24 = new byte[size * 3];
	for (int i = 0; i < size; i++)
	{
		RGBFloat pixel = image->pixels[i];
		bgr24[i * 3 + 0] = (byte) (pixel.b * 255);
		bgr24[i * 3 + 1] = (byte) (pixel.g * 255);
		bgr24[i * 3 + 2] = (byte) (pixel.r * 255);
	}
	BitmapHeader* header = new BitmapHeader();

	header->type = MagicIdentifier;
	header->fileSize = sizeof(BitmapHeader) + size * 3;
	header->reserved1 = 0;
	header->reserved2 = 0;
	header->offset = sizeof(BitmapHeader);
	header->headerSize = sizeof(BitmapHeader) - BaseHeaderSize;
	header->width = w;
	header->height = h;
	header->planes = 1;
	header->bits = 24;
	header->compression = 0;
	header->imgSize = 0;
	header->xResolution = 0;
	header->yYesolution = 0;
	header->nColours = 0;
	header->impColours = 0;
	stream->write((char*) header, sizeof(BitmapHeader));
	stream->write((char*) bgr24, (long long ) size * 3);
}
