#pragma once

#include <fstream>

#include "ImageType.h"
#include "BitmapHeader.h"
#include "Types.h"
#include "Scene.h"
#include "InputHandler.h"
constexpr int MagicIdentifier = 19778;
constexpr int BaseHeaderSize = 14;

class Bitmap : public ImageType
{
	private: 
	
		byte* ReadData(std::ifstream*& stream, BitmapHeader*& bmpHeader);
		void ReadHeader(std::ifstream*& stream, BitmapHeader*& bmpHeader);

	public:

		Image* Read(std::ifstream*, Scene* scene, InputHandler* input);
		void Write(Image* image, std::ofstream*);
};

