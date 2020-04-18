#pragma once

#include <fstream>
#include <ostream>
#include <vector>
class Serial
{
	public:
	template <typename T>
	static T Read(std::ifstream& stream)
	{
		T t;
		stream.read((char*)&t, sizeof(T));
		return t;
	}

	template <typename T>
	static void Write(std::ofstream& stream, T t)
	{
		stream.write((const char*)&t, sizeof(T));
	}
};

