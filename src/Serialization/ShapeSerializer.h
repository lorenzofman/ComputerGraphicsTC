#pragma once
#include <fstream>
#include <ostream>
#include <iostream>

#include "Serial.h"
#include "../Shapes/Shape.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Polygon.h"
#include "../DataStructures/Array.h"
#include "../Primitives/Types.h"



class ShapeSerializer
{
	public:

	static void Serialize(const char* path, Array<Shape*>);
	static Array<Shape*> Deserialize(const char* path);

	private:
	static void Serialize(std::ofstream&, Array<Shape*>);
	static Array<Shape*> Deserialize(std::ifstream&);
	static Shape* DeserializeShape(std::ifstream&);
};

