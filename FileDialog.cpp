#include <stdlib.h>

#include "FileDialog.h"

#define VS
//#undef VS /*If running on CodeBlocks */

bool FileDialog::IsDialogOpen = false;
OPENFILENAME FileDialog::CreateOfn(LPWSTR buffer)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = nullptr;
	ofn.lpstrFile = buffer;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = nullptr;
	return ofn;
}

std::string FileDialog::Open()
{
	if (IsDialogOpen)
	{
		return std::string();
	}
	IsDialogOpen = true;
	char buffer[MAX_PATH];
	LPWSTR lpwstrFileName = (LPWSTR)buffer;
	OPENFILENAME ofn = CreateOfn(lpwstrFileName);

	if (GetOpenFileName(&ofn) == false)
	{
		IsDialogOpen = false;
		return std::string();
	}
	IsDialogOpen = false;
	char fileName[MAX_PATH];
	size_t size;
	wcstombs_s(&size, fileName, lpwstrFileName, MAX_PATH);
	return std::string(fileName);
}

std::string FileDialog::Save()
{
	if (IsDialogOpen)
	{
		return std::string();
	}
	IsDialogOpen = true;
	char buffer[MAX_PATH];
	buffer[0] = '\0';
	LPWSTR lpwstrFileName = (LPWSTR)buffer;
	OPENFILENAME ofn = CreateOfn(lpwstrFileName);

	if (GetSaveFileName(&ofn) == false)
	{
		IsDialogOpen = false;
		return std::string();
	}
	IsDialogOpen = false;
	char fileName[MAX_PATH];
	size_t size;
	wcstombs_s(&size, fileName, lpwstrFileName, MAX_PATH);
	return std::string(fileName);
}
