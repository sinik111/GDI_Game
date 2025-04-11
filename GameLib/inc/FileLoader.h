#pragma once

#include <string>

namespace Gdiplus
{
	class Bitmap;
}

enum class ResultCode;

class FileLoader
{
private:
	wchar_t resource_path[260];
	const wchar_t* binary_folder_name;
	const wchar_t* resource_folder_name;

private:
	FileLoader();

public:
	static FileLoader& GetInstance();

public:
	ResultCode Initialize(const wchar_t* binary_folder_name, const wchar_t* resource_folder_name);
	std::string* LoadTextFile(const wchar_t* file_name);
	Gdiplus::Bitmap* LoadImageFile(const wchar_t* file_name);
};