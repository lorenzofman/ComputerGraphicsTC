#include <stdlib.h>

#include "FileDialog.h"

LPCWSTR S2WS(const std::string& str)
{
	return std::wstring(str.begin(), str.end()).c_str();
}

OPENFILENAME FileDialog::CreateOfn(std::string filter)
{
	OPENFILENAME ofn;
	wchar_t* fileName = new wchar_t[MAX_PATH];
	fileName[0] = '\0';
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = S2WS(filter);
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";
	return ofn;
}

std::string FileDialog::Open(std::string filter)
{
	OPENFILENAME ofn = CreateOfn(filter);

	if (GetOpenFileName(&ofn) == false)
	{
		return std::string();
	}
	char fileName[MAX_PATH];
	fileName[0] = '\0';
	size_t size;
	wcstombs_s(&size, fileName, ofn.lpstrFile, MAX_PATH);

	delete ofn.lpstrFile;

	return std::string(fileName);
}

std::string FileDialog::Save(std::string filter)
{
	return std::string();
}
