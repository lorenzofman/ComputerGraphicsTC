#pragma once

#include <fstream>
#include <vector>

#include "Types.h"
#include "Shape.h"

constexpr byte RectangleId	= 0xff;
constexpr byte CircleId		= 0xfe;
constexpr byte PolygonId	= 0xfd;

class Serial
{
	static Shape** Deserialize(std::ifstream&);
	static Shape* DeserializeShape(std::ifstream&);
	template <typename T>
	static T Read(std::ifstream& stream)
	{
		T t;
		stream.read((char*)&t, sizeof(T));
		return t;
	}
};

