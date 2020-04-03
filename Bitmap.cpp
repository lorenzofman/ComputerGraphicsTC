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
	int bytesPerLine = (3 * (bmpHeader->width + 1) / 4) * 4;
	int size = bmpHeader->width * bmpHeader->height * 3;
	byte* data = new byte[bytesPerLine * bmpHeader->height];
	stream->read((char*)data, size);
	return data;
}
RGBFloat* ConvertBGR24ToPadLessRGBFloat(byte* arr, int w, int h, int bytesPerLine)
{
	int size = bytesPerLine * h;
	RGBFloat* buffer = new RGBFloat[size];
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < h; x++)
		{
			int srcIdx = y * bytesPerLine + x * 3;
			int dstIdx = y * w + x;
			float b = arr[srcIdx + 0] / 255.0f;
			float g = arr[srcIdx + 1] / 255.0f;
			float r = arr[srcIdx + 2] / 255.0f;
			buffer[dstIdx] = RGBFloat(r, g, b);
		}
	}
	return buffer;
}
Image* Bitmap::Read(std::ifstream* stream, Scene* scene, InputHandler* input)
{
	BitmapHeader* bmpHeader = new BitmapHeader();
	ReadHeader(stream, bmpHeader);
	ValidateFile(bmpHeader);
	byte* data = ReadData(stream, bmpHeader);
	int bytesPerLine = (3 * (bmpHeader->width + 1) / 4) * 4;
	RGBFloat* fDataPadLess = ConvertBGR24ToPadLessRGBFloat(data, bmpHeader->width, bmpHeader->height, bytesPerLine);
	return new Image(fDataPadLess, bmpHeader->width, bmpHeader->height, scene, input);
}

byte* ConvertPixelsToPaddedByteArray(RGBFloat* arr, int w, int h)
{
	int bytesPerLine = (3 * (w + 1) / 4) * 4;
	byte* bgr24 = new byte[bytesPerLine * h];
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int srcIdx = y * w + x;
			int destIdx = y * bytesPerLine + x * 3;
			bgr24[destIdx + 0] = (byte)(arr[srcIdx].b * 255);
			bgr24[destIdx + 1] = (byte)(arr[srcIdx].g * 255);
			bgr24[destIdx + 2] = (byte)(arr[srcIdx].r * 255);
		}
	}
	return bgr24;
}

void Bitmap::Write(Image* image, std::ofstream* stream)
{
	int w = image->width;
	int h = image->height;
	int size = h * w;
	byte* bgr24 = ConvertPixelsToPaddedByteArray(image->pixels, w, h);
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
	stream->write((char*) bgr24, (long long) size * 3);
}
