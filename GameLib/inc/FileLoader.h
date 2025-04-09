#pragma once

#include <string>

namespace Gdiplus
{
	class Bitmap;
}

enum ResultCode;

class FileLoader
{
private:
	wchar_t data_path[260];
	const wchar_t* binary_folder_name;
	const wchar_t* resource_folder_name;

public:
	FileLoader(const wchar_t* binary_folder_name, const wchar_t* resource_folder_name);

public:
	ResultCode Initialize();
	std::string* LoadTextFile(const wchar_t* file_name);
	Gdiplus::Bitmap* LoadImageFile(const wchar_t* file_name);
};