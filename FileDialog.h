#pragma once
#include <string>
#include <Windows.h>
#include <commdlg.h>
class FileDialog
{
	public:
		static std::string Open();
		static std::string Save();
	private:
		static OPENFILENAME CreateOfn(LPWSTR buffer);
		static bool IsDialogOpen;
};

