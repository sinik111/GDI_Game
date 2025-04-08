#include "GDIRenderer.h"

#include <windows.h>
#include <gdiplus.h>

#include "DebugUtility.h"
#include "ResultCode.h"

#pragma comment(lib, "gdiplus.lib")

GDIRenderer::GDIRenderer(HWND hwnd, int width, int height)
	: hwnd(hwnd), width(width), height(height), front_buffer_dc(nullptr), back_buffer_dc(nullptr),
	back_buffer_bitmap(nullptr), gdiplus_token(0), back_buffer_graphics(nullptr)
{
	DebugLog("GDIRenderer 생성됨");
}

GDIRenderer::~GDIRenderer()
{
	DebugLog("GDIRenderer 소멸됨");
}

ResultCode GDIRenderer::Initialize()
{
	DebugLog("GDIRenderer::Initialize()");

	front_buffer_dc = GetDC(hwnd); // 윈도우 클라이언트 영역의 Device Context 얻기
	if (front_buffer_dc == nullptr)
	{
		DebugLog("GetDC 실패 - GDIRenderer::Initialize()");

		return RESULT_FAIL;
	}

	back_buffer_dc = CreateCompatibleDC(front_buffer_dc); // 호환되는 Device Context 생성
	if (back_buffer_dc == nullptr)
	{
		DebugLog("CreateCompatibleDC 실패 - GDIRenderer::Initialize()");

		return RESULT_FAIL;
	}

	back_buffer_bitmap = CreateCompatibleBitmap(front_buffer_dc, width, height); // 메모리 영역 생성
	if (back_buffer_bitmap == nullptr)
	{
		DebugLog("CreateCompatibleBitmap 실패 - GDIRenderer::Initialize()");

		return RESULT_FAIL;
	}

	SelectObject(back_buffer_dc, back_buffer_bitmap); // MemDC의 메모리 영역 지정

	Gdiplus::GdiplusStartupInput gsi;
	Gdiplus::Status status = Gdiplus::GdiplusStartup(&gdiplus_token, &gsi, nullptr);
	if (status != Gdiplus::Ok)
	{
		DebugLog("Gdiplus::GdiplusStartup 실패 status: %d - GDIRenderer::Initialize()", (int)status);

		return RESULT_FAIL;
	}
	
	back_buffer_graphics = Gdiplus::Graphics::FromHDC(back_buffer_dc);
	if (back_buffer_graphics == nullptr)
	{
		DebugLog("Gdiplus::Graphics::FromHD 실패 - GDIRenderer::Initialize()");

		return RESULT_FAIL;
	}

	return RESULT_OK;
}

void GDIRenderer::Shutdown()
{
	DebugLog("GDIRenderer::Shutdown()");

	if (back_buffer_graphics != nullptr)
	{
		delete back_buffer_graphics;
		back_buffer_graphics = nullptr;
	}

	if (gdiplus_token != 0)
	{
		Gdiplus::GdiplusShutdown(gdiplus_token);
		gdiplus_token = 0;
	}

	if (back_buffer_bitmap != nullptr)
	{
		DeleteObject(back_buffer_bitmap);
		back_buffer_bitmap = nullptr;
	}
	
	if (back_buffer_dc != nullptr)
	{
		DeleteDC(back_buffer_dc);
		back_buffer_dc = nullptr;
	}
	
	if (front_buffer_dc != nullptr)
	{
		ReleaseDC(hwnd, front_buffer_dc);
		front_buffer_dc = nullptr;
	}
}

void GDIRenderer::BeginDraw()
{
	PatBlt(back_buffer_dc, 0, 0, width, height, BLACKNESS);
}

void GDIRenderer::DrawImage(Gdiplus::Bitmap* image, Gdiplus::Rect& dst_rect, Gdiplus::Rect& src_rect)
{
	back_buffer_graphics->DrawImage(image, dst_rect, src_rect.X, src_rect.Y, src_rect.Width, src_rect.Height, Gdiplus::UnitPixel);
}

void GDIRenderer::EndDraw()
{
	BitBlt(front_buffer_dc, 0, 0, width, height, back_buffer_dc, 0, 0, SRCCOPY);
}