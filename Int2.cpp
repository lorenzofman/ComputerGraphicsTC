#include <cmath>

#include "Int2.h"
Int2::Int2()
{
	x = y = 0;
}

Int2::Int2(Float2 floating)
{
	this->x = (int)floating.x;
	this->y = (int)floating.y;
}

Int2::Int2(int x, int y)
{
	this->x = x;
	this->y = y;
}

Int2 Int2::operator+(Int2 const& obj)
{
	return Int2(x + obj.x, y + obj.y);
}

void Int2::operator+=(Int2 const& obj)
{
	x += obj.x;
	y += obj.y;
}

Int2 Int2::operator*(int constant)
{
	return Int2(x * constant, y * constant);
}

void Int2::operator*=(int constant)
{
	x *= constant;
	y *= constant;
}

void Int2::Rotate(double rot)
{
	int x0 = x;
	x = (int)(x0 * cos(rot) - y * sin(rot));
	y = (int)(x0 * sin(rot) + y * cos(rot));
}