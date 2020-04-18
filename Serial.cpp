#include "Serial.h"

Shape** Serial::Deserialize(std::ifstream& stream)
{
	int elements = Read<int>(stream);
	Shape** shapes = new Shape* [elements];
	for (int i = 0; i < elements; i++)
	{
		shapes[i] = DeserializeShape(stream);
	}
}

Shape* Serial::DeserializeShape(std::ifstream& stream)
{
	byte id = Read<byte>(stream);
	switch (id)
	{
		case RectangleId:
			
			break;
		case CircleId:
			break;
		case PolygonId:
			break;
	}
}
