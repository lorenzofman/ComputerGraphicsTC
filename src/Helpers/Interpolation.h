#pragma once
class Interpolation
{
	public:
	template <typename T>
	static T Linear(const T a, const T b, const float t)
	{
		return a + (b - a) * t;
	}

	template <typename T>
	static T Quadratic(const T a, const  T b, const T c, const  float t)
	{
		const T p0 = Linear(a, b, t);
		const T p1 = Linear(b, c, t);
		return Linear(p0, p1, t);
	}

	template <typename T>
	static T Cubic(const T a, const T b, const  T c, const  T d, const float t)
	{
		const T p0 = Quadratic(a, b, c, t);
		const T p1 = Quadratic(b, c, d, t);
		return Linear(p0, p1, t);
	}
};