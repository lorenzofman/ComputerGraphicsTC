#pragma once
struct Int2;
#include "Int2.h"
struct Float2
{
	float x, y;

	Float2();
	Float2(Int2 integer);
	Float2(float x, float y);

	Float2 operator + (Float2 const& obj);
	void operator += (Float2 const& obj);

	Float2 operator - (Float2 const& obj);
	void operator -= (Float2 const& obj);
	
	Float2 operator * (float const& constant);
	void operator *= (float const& constant);
	void Rotate(double rot);

	static float Distance(Float2 a, Float2 b);
	static float DistanceSq(Float2 a, Float2 b);

};