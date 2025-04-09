#include "FileLoader.h"

#include <windows.h>
#include <fstream>
#include <string>
#include <gdiplus.h>

#include "ResultCode.h"

FileLoader::FileLoader(const wchar_t* binary_folder_name, const wchar_t* resource_folder_name)
	: data_path(L""), binary_folder_name(binary_folder_name), resource_folder_name(resource_folder_name)
{

}

ResultCode FileLoader::Initialize()
{
	GetModuleFileNameW(NULL, data_path, MAX_PATH);

	size_t path_length = wcslen(data_path);
	bool wrong_directory = true;

	for (int i = (int)path_length - 1; i >= 0; --i)
	{
		if (data_path[i] == L'\\')
		{
			data_path[i] = L'\0';

			if (!wcscmp(binary_folder_name, &(data_path[i + 1])))
			{
				wrong_directory = false;

				break;
			}
		}
	}

	if (wrong_directory)
	{
		return RESULT_FAIL;
	}
	
	wcscat_s(data_path, MAX_PATH, L"\\");
	wcscat_s(data_path, MAX_PATH, resource_folder_name);
	wcscat_s(data_path, MAX_PATH, L"\\");

	return RESULT_OK;
}


std::string* FileLoader::LoadTextFile(const wchar_t* file_name)
{
	wchar_t file_path[MAX_PATH] = {};

	memcpy(file_path, data_path, sizeof(file_path));

	wcscat_s(file_path, MAX_PATH, file_name);

	std::ifstream stream(file_path);

	if (!stream.is_open())
	{
		return nullptr;
	}

	std::string* data = new std::string("");

	std::string line;
	while (std::getline(stream, line))
	{
		*data += " " + line;
	}

	stream.close();

	return data;
}

Gdiplus::Bitmap* FileLoader::LoadImageFile(const wchar_t* file_name)
{
	wchar_t file_path[MAX_PATH] = {};

	memcpy(file_path, data_path, sizeof(file_path));

	wcscat_s(file_path, MAX_PATH, file_name);

	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(file_path);

	if (image->GetLastStatus())
	{
		delete image;

		return nullptr;
	}

	return image;
}