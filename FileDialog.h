#pragma once
#include <string>
#include <Windows.h>
class FileDialog
{
	private:
		static OPENFILENAME CreateOfn(DWORD flags);
	public:
		static std::string Open();
		static std::string Save();
};

