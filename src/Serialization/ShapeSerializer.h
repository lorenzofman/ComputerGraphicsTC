#pragma once
#include <fstream>
#include <ostream>
#include <iostream>

#include "Array.h"
#include "Types.h"
#include "Shape.h"
#include "Serial.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Polygon.h"



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

