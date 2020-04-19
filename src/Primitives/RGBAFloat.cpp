#include "RGBAFloat.h"

RGBAFloat::RGBAFloat()
{
	r = g = b = a = .0f;
}

RGBAFloat::RGBAFloat(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

RGBAFloat RGBAFloat::operator*(float const& constant) const
{
	return RGBAFloat(r * constant, g * constant, b * constant, a * constant);
}

void RGBAFloat::operator*=(float const& constant)
{
	r *= constant;
	g *= constant;
	b *= constant;
	a *= constant;
}

RGBAFloat RGBAFloat::Blank = RGBAFloat(0, 0, 0, 0);