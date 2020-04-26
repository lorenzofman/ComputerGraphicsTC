#pragma once
class Interpolation
{
	public:
	template <typename T>
	static T Linear(T a, T b, float t)
	{
		return a + (b - a) * t;
	}

	template <typename T>
	static T Quadratic(T a, T b, T c, float t)
	{
		T p0 = Linear(a, b, t);
		T p1 = Linear(b, c, t);
		return Linear(p0, p1, t);
	}

	template <typename T>
	static T Cubic(T a, T b, T c, T d, float t)
	{
		T p0 = Quadratic(a, b, c, t);
		T p1 = Quadratic(b, c, d, t);
		return Linear(p0, p1, t);
	}
};