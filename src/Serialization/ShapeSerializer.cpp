#include "ShapeSerializer.h"

void ShapeSerializer::Serialize(const char* path, Array<Shape*> shapes)
{
	if (path == nullptr)
	{
		return;
	}
	std::ofstream stream = std::ofstream(path, std::ios::out | std::ios::binary);
	Serialize(stream, shapes);
	stream.close();
}

Array<Shape*> ShapeSerializer::Deserialize(const char* path)
{
	if (path == nullptr)
	{
		return Array<Shape*>();
	}
	std::ifstream stream = std::ifstream(path, std::ios::in | std::ios::binary);
	Array<Shape*> arr = Deserialize(stream);
	stream.close();
	return arr;
}

void ShapeSerializer::Serialize(std::ofstream& stream, Array<Shape*> shapes)
{
	Serial::Write<int>(stream, shapes.size);
	for (int i = 0; i < shapes.size; i++)
	{
		shapes[i]->Serialize(stream);
	}
}

Array<Shape*> ShapeSerializer::Deserialize(std::ifstream& stream)
{
	int elements = Serial::Read<int>(stream);
	Shape** shapes = new Shape * [elements];
	for (int i = 0; i < elements; i++)
	{
		shapes[i] = DeserializeShape(stream);
	}
	return Array<Shape*>(shapes, elements);
}

Shape* ShapeSerializer::DeserializeShape(std::ifstream& stream)
{
	byte id = Serial::Read<byte>(stream);
	switch (id)
	{
		case RectangleId:
			return new class Rectangle(stream);
		case CircleId:
			return new class Circle(stream);
		case PolygonId:
			return new class Polygon(stream);
		default:
			exit(1);
	}
}
