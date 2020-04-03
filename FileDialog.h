#pragma once
#include <string>
#include <Windows.h>
class FileDialog
{
	public:
		static std::string Open();
		static std::string Save();
	private:
		static OPENFILENAME CreateOfn(DWORD flags);
		static bool IsDialogOpen;
};

