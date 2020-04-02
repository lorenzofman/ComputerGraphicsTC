#include <stdlib.h>

#include "FileDialog.h"

OPENFILENAME FileDialog::CreateOfn(DWORD flags)
{
	OPENFILENAME ofn;
	wchar_t* fileName = new wchar_t[MAX_PATH];
	fileName[0] = '\0';
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = nullptr;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";
	return ofn;
}

std::string FileDialog::Open()
{
	OPENFILENAME ofn = CreateOfn(OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

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

std::string FileDialog::Save()
{
	OPENFILENAME ofn = CreateOfn(OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY);

	if (GetSaveFileName(&ofn) == false)
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
