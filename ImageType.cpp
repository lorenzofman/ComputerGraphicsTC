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
Image* ImageType::Read(std::string path, std::string extension, Scene* scene)
{
	std::ifstream* stream = new std::ifstream(path, std::ifstream::binary);
	if (stream->is_open() == false)
	{
		std::cout << "Couldn't open file: ";
		exit(0);
	}
	ImageType* imageType = SelectProperImageType(extension);
	return imageType->Read(stream, scene);
}

void ImageType::Write(Image*, std::ofstream*, std::string extension)
{

}
