#pragma once
struct Float2
{
	float x, y;

	Float2();
	Float2(float x, float y);

	Float2 operator + (Float2 const& obj);
	void operator += (Float2 const& obj);
	
	Float2 operator * (float constant);
	void operator *= (float constant);
	void Rotate(double rot);
};