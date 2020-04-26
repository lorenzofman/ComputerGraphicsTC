#pragma once
struct Int2;
#include "Int2.h"
struct Float2
{
	float x, y;

	Float2();
	Float2(Int2 integer);
	Float2(float x, float y);
	Float2 operator + (Float2 const& obj) const;
	void operator += (Float2 const& obj);

	Float2 operator -() const;
	Float2 operator - (Float2 const& obj) const;
	void operator -= (Float2 const& obj);
	
	Float2 operator * (float const& constant) const;
	void operator *= (float const& constant);
	void Rotate(float rot);
	float GetLength();
	void Normalize();
	Float2 GetNormalized();
	Float2 PerpendicularClockwise();
	Float2 PerpendicularCounterClockwise();

	static float Distance(Float2 a, Float2 b);
	static float DistanceSq(Float2 a, Float2 b);
	static float Angle(Float2 a, Float2 b);

	static const Float2 Zero;
	static const Float2 One;
	static const Float2 Up;
	static const Float2 Down;
	static const Float2 Right;
	static const Float2 Left;
};