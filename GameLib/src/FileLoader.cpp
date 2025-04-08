#include "FileLoader.h"

#include <windows.h>
#include <fstream>
#include <string>
#include <gdiplus.h>

static wchar_t data_path[MAX_PATH] = {};

void FileLoader::Initialize(const wchar_t* binary_folder_name, const wchar_t* data_folder_name)
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
		return;
	}
	
	wcscat_s(data_path, MAX_PATH, L"\\");
	wcscat_s(data_path, MAX_PATH, data_folder_name);
	wcscat_s(data_path, MAX_PATH, L"\\");
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

	Gdiplus::Bitmap* image = new Gdiplus::Bitmap(file_name);

	if (image->GetLastStatus())
	{
		delete image;

		return nullptr;
	}

	return image;
}


//StringData* LoadSingleLineData(const wchar_t* file_name)
//{
//	wchar_t path[MAX_PATH] = { 0 };
//
//	GetModuleFileNameW(NULL, path, MAX_PATH);
//
//	size_t path_length = wcslen(path);
//	BOOL no_file = TRUE;
//
//	for (int i = (int)path_length - 1; i >= 0; --i)
//	{
//		if (path[i] == '\\')
//		{
//			path[i] = '\0';
//
//			if (!wcscmp(L"bin", &(path[i + 1])))
//			{
//				no_file = FALSE;
//
//				break;
//			}
//		}
//	}
//
//	if (no_file)
//	{
//		DebugLog("파일을 열 수 없습니다. LoadData()\n");
//		return NULL;
//	}
//
//	wcscat_s(path, MAX_PATH, L"\\data\\");
//	wcscat_s(path, MAX_PATH, file_name);
//
//	FILE* fp = _wfopen(path, L"r, ccs=UTF-8");
//	if (fp == NULL)
//	{
//		DebugLog("파일을 열 수 없습니다. LoadData()\n");
//		return NULL;
//	}
//
//	StringData* sd = (StringData*)malloc(sizeof(StringData));
//	if (sd == NULL)
//	{
//		fclose(fp);
//		DebugLog("sd 할당 실패. LoadData()\n");
//		return NULL;
//	}
//
//	wchar_t header[100];
//
//	fgetws(header, 100, fp);
//	fgetws(header, 100, fp);
//
//	int result = swscanf(header, L"%d %d %d %d %d %d",
//		&sd->m, &sd->n, &sd->count, &sd->additional1, &sd->additional2, &sd->additional3);
//
//	sd->data = (wchar_t*)malloc(sizeof(wchar_t) * (sd->m * sd->n * sd->count + 1));
//	if (sd->data == NULL)
//	{
//		fclose(fp);
//		printf("sd->data 할당 실패. LoadData()\n");
//		return NULL;
//	}
//
//	wmemset(sd->data, 0, sd->m * sd->n * sd->count);
//
//	fgetws(sd->data, sd->m * sd->n * sd->count + 1, fp);
//
//	fclose(fp);
//
//	return sd;
//}
//
//StringData* LoadMultiLineData(const wchar_t* file_name)
//{
//	wchar_t path[MAX_PATH] = { 0 };
//
//	GetModuleFileNameW(NULL, path, MAX_PATH);
//
//	size_t path_length = wcslen(path);
//	BOOL no_file = TRUE;
//
//	for (int i = (int)path_length - 1; i >= 0; --i)
//	{
//		if (path[i] == '\\')
//		{
//			path[i] = '\0';
//
//			if (!wcscmp(L"bin", &(path[i + 1])))
//			{
//				no_file = FALSE;
//
//				break;
//			}
//		}
//	}
//
//	if (no_file)
//	{
//		DebugLog("파일을 열 수 없습니다. LoadData()\n");
//		return NULL;
//	}
//
//	wcscat_s(path, MAX_PATH, L"\\data\\");
//	wcscat_s(path, MAX_PATH, file_name);
//
//	FILE* fp = _wfopen(path, L"r, ccs=UTF-8");
//	if (fp == NULL)
//	{
//		DebugLog("파일을 열 수 없습니다. LoadData()\n");
//		return NULL;
//	}
//
//	StringData* sd = (StringData*)malloc(sizeof(StringData));
//	if (sd == NULL)
//	{
//		fclose(fp);
//		DebugLog("sd 할당 실패. LoadData()\n");
//		return NULL;
//	}
//
//	wchar_t header[100];
//
//	fgetws(header, 100, fp);
//	fgetws(header, 100, fp);
//
//	int result = swscanf(header, L"%d", &sd->count);
//
//	sd->data = (wchar_t*)malloc(sizeof(wchar_t) * 200 * sd->count);
//	if (sd->data == NULL)
//	{
//		fclose(fp);
//		printf("sd->data 할당 실패. LoadData()\n");
//		return NULL;
//	}
//
//	wmemset(sd->data, 0, 200 * sd->count);
//
//	wchar_t line[200];
//
//	for (int i = 0; i < sd->count; ++i)
//	{
//		wmemset(line, 0, 200);
//
//		fgetws(line, 200, fp);
//		line[wcscspn(line, L"\n")] = L'\t';
//		wcscat_s(sd->data, 200 * sd->count, line);
//	}
//
//	fclose(fp);
//
//	return sd;
//}