#include "FileLoader.h"

#include <windows.h>
#include <fstream>
#include <string>
#include <gdiplus.h>

#include "ResultCode.h"

FileLoader::FileLoader()
	: resource_path(L""), binary_folder_name(nullptr), resource_folder_name(nullptr)
{

}

FileLoader& FileLoader::GetInstance()
{
	static FileLoader instance;

	return instance;
}

ResultCode FileLoader::Initialize(const wchar_t* binary_folder_name, const wchar_t* resource_folder_name)
{
	GetModuleFileNameW(NULL, resource_path, MAX_PATH);

	size_t path_length = wcslen(resource_path);
	bool wrong_directory = true;

	for (int i = (int)path_length - 1; i >= 0; --i)
	{
		if (resource_path[i] == L'\\')
		{
			resource_path[i] = L'\0';

			if (!wcscmp(binary_folder_name, &(resource_path[i + 1])))
			{
				wrong_directory = false;

				break;
			}
		}
	}

	if (wrong_directory)
	{
		return ResultCode::FAIL;
	}
	
	wcscat_s(resource_path, MAX_PATH, L"\\");
	wcscat_s(resource_path, MAX_PATH, resource_folder_name);
	wcscat_s(resource_path, MAX_PATH, L"\\");

	return ResultCode::OK;
}


std::string* FileLoader::LoadTextFile(const wchar_t* file_name)
{
	wchar_t file_path[MAX_PATH] = {};

	memcpy(file_path, resource_path, sizeof(file_path));

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

	memcpy(file_path, resource_path, sizeof(file_path));

	wcscat_s(file_path, MAX_PATH, file_name);

	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(file_path);

	if (image->GetLastStatus())
	{
		delete image;

		return nullptr;
	}

	return image;
}