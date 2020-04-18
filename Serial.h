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
	static std::vector<Shape*> Deserialize(std::ifstream);
	static Shape* DeserializeShape(std::ifstream);
};

