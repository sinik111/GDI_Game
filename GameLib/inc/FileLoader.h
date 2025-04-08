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

public:
	static FileLoader& GetInstance();

public:
	ResultCode Initialize(const wchar_t* binary_folder_name, const wchar_t* resource_folder_name);
	std::string* LoadTextFile(const wchar_t* file_name);
	Gdiplus::Bitmap* LoadImageFile(const wchar_t* file_name);

private:
	FileLoader() = default;
	~FileLoader() = default;
	FileLoader(FileLoader&) = delete;
	FileLoader operator=(FileLoader&) = delete;
	FileLoader(FileLoader&&) = delete;
};




//typedef struct StringData
//{
//	int m;
//	int n;
//	int count;
//	int additional1;
//	int additional2;
//	int additional3;
//	wchar_t* data;
//} StringData;
//
//
//
//
//StringData* LoadSingleLineData(const wchar_t* file_name);
//
//StringData* LoadMultiLineData(const wchar_t* file_name);