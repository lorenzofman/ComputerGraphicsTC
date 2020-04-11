#include <cmath>

#include "Float2.h"
Float2::Float2()
{
	x = y = 0;
}

Float2::Float2(Int2 integer)
{
	this->x = (float)integer.x;
	this->y = (float)integer.y;
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

Float2 Float2::operator-()
{
	return Float2(-x, -y);
}

Float2 Float2::operator-(Float2 const& obj)
{
	return Float2(x - obj.x, y - obj.y);
}

void Float2::operator-=(Float2 const& obj)
{
	x -= obj.x;
	y -= obj.y;
}

Float2 Float2::operator*(float const &constant)
{
	return Float2(x * constant, y * constant);
}

void Float2::operator*=(float const& constant)
{
	x *= constant;
	y *= constant;
}

void Float2::Rotate(float rot)
{
	float x0 = x;
	x = (float) (x0 * cosf(rot) - y * sinf(rot));
	y = (float) (x0 * sinf(rot) + y * cosf(rot));
}

float Float2::Distance(Float2 a, Float2 b)
{
	return sqrtf(DistanceSq(a,b));
}

float Float2::DistanceSq(Float2 a, Float2 b)
{
	float xDif = b.x - a.x;
	float yDif = b.y - a.y;
	return xDif * xDif + yDif * yDif;
}
