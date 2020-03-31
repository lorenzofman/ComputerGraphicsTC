#include <cmath>

#include "Float2.h"
Float2::Float2()
{
	x = y = 0;
}

Float2::Float2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Float2 Float2::operator+(Float2 const& obj)
{
	return Float2(x + obj.x, y + obj.y);
}

void Float2::operator+=(Float2 const& obj)
{
	x += obj.x;
	y += obj.y;
}

Float2 Float2::operator*(float constant)
{
	return Float2(x * constant, y * constant);
}

void Float2::operator*=(float constant)
{
	x *= constant;
	y *= constant;
}

void Float2::Rotate(double rot)
{
	float x0 = x;
	x = (float) (x0 * cos(rot) - y * sin(rot));
	y = (float) (x0 * sin(rot) + y * cos(rot));
}