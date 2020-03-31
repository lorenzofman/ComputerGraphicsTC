#pragma once
#include <string>
#include <Windows.h>
class FileDialog
{
	private:
		static OPENFILENAME CreateOfn(std::string filter);
	public:
		static std::string Open(std::string filter);
		static std::string Save(std::string filter);
};

