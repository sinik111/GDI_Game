#pragma once

#include <windows.h>
#include <gdiplus.h>

enum ResultCode;

class GDIRenderer
{
private:
	// 윈도우 정보
	HWND hwnd;
	int width;
	int height;

	// 버퍼
	HDC front_buffer_dc;
	HDC back_buffer_dc;

	HBITMAP back_buffer_bitmap;

	// GDI+
	ULONG_PTR gdiplus_token;
	Gdiplus::Graphics* back_buffer_graphics;

public: // 생성자, 소멸자
	GDIRenderer(HWND hwnd, int width, int height);
	~GDIRenderer();

public: // 초기화, 정리
	ResultCode Initialize();
	void Shutdown();

public: // 그리기
	void BeginDraw();
	void DrawImage(Gdiplus::Bitmap* image, Gdiplus::Rect& dst_rect, Gdiplus::Rect& src_rect);
	void EndDraw();
};