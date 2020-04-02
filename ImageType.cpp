#include <fstream>
#include <iostream>
#include "ImageType.h"
#include "Bitmap.h"

ImageType* SelectProperImageType(std::string extension)
{
	if (extension.compare("bmp") == 0)
	{
		return new Bitmap();
	}

	throw "Unsupported file format";
}
constexpr auto MaxPath = 1000;
Image* ImageType::Read(std::string path, std::string extension, Scene* scene, InputHandler* input)
{
	std::ifstream* stream = new std::ifstream(path, std::ifstream::binary);
	if (stream->is_open() == false)
	{
		std::cout << "Couldn't open file: ";
		exit(0);
	}
	ImageType* imageType = SelectProperImageType(extension);
	Image* img = imageType->Read(stream, scene, input);
	stream->close();
	return img;
}

void ImageType::Write(Image* img, std::string path, std::string extension)
{
	std::ofstream* stream = new std::ofstream(path, std::ofstream::binary);
	if (stream->is_open() == false)
	{
		std::cout << "Couldn't open file: ";
		exit(0);
	}
	ImageType* imageType = SelectProperImageType(extension);
	imageType->Write(img, stream);
	stream->close();
}
