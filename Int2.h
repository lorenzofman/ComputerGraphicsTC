#pragma once
struct Float2;
#include "Float2.h"
struct Int2
{
	int x, y;

	Int2();
	Int2(Float2 floating);
	Int2(int x, int y);

	Int2 operator + (Int2 const& obj);
	void operator += (Int2 const& obj);

	Int2 operator * (int constant);
	void operator *= (int constant);
	void Rotate(double rot);
};