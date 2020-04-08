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