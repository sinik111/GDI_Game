#pragma once

#include <string>

namespace Gdiplus
{
	class Bitmap;
}

class FileLoader
{
public:
	void Initialize(const wchar_t* binary_folder_name, const wchar_t* data_folder_name);
	std::string* LoadTextFile(const wchar_t* file_name);
	Gdiplus::Bitmap* LoadImageFile(const wchar_t* file_name);
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