#include <fstream>
#include <iostream>
#include "Bitmap.h"
#include "Image.h"

void Bitmap::ReadHeader(std::ifstream*& stream, BitmapHeader*& bmpHeader)
{
	stream->read((char*)bmpHeader, sizeof(BitmapHeader));
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
			throw "Non RGB BMP is not supported yet";
		}

		if (bmpHeader->planes != 1)
		{
			throw "Number of planes is not supported yet";
		}

		if (bmpHeader->width * bmpHeader->height * 3 != bmpHeader->imgSize)
		{
			printf("Warning: BMP file is NPOT\n");
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
	byte* data = new byte[bmpHeader->fileSize];
	stream->read((char*)data, bmpHeader->fileSize);
	return data;
}

Image* Bitmap::Read(std::ifstream* stream, Scene* scene)
{
	BitmapHeader* bmpHeader = new BitmapHeader();
	ReadHeader(stream, bmpHeader);
	ValidateFile(bmpHeader);
	byte* data = ReadData(stream, bmpHeader);
	return new Image{ data, bmpHeader->fileSize, ColorSpace::BGR24, bmpHeader->width, bmpHeader->height, scene};
}



void Bitmap::Write(Image* image, std::ofstream* stream)
{

}
