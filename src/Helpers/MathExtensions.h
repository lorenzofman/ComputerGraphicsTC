#pragma once
class MathExtensions
{
	public:
	template<typename T>
	static T Factorial(T val)
	{
		if (val == 0)
		{
			return 1;
		}

		T factorial = val;
		while (--val > 0)
		{
			factorial *= val;
		}
		return factorial;
	}

	template<typename T>
	static T Binomial(T n, T i)
	{
		return Factorial(n) / (Factorial(i) * Factorial(n - i));
	}
};

