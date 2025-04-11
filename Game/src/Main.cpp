#include <windows.h>

#include "MyTime.h"
#include "DebugUtility.h"
#include "Game.h"
#include "ResultCode.h"

struct WindowInfo
{
	HWND hwnd;
	HINSTANCE hinstance;
	LPCTSTR class_name;
	LPCTSTR window_name;
	int width;
	int height;
	int cmd_show;
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static ResultCode InitializeWindow(WindowInfo& window_info);

// main
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ENABLE_LEAK_CHECK();

	InitializeConsole();

	ResultCode rc = ResultCode::OK;

	WindowInfo window_info;
	window_info.hwnd = nullptr;
	window_info.hinstance = hInstance;
	window_info.class_name = TEXT("GDI");
	window_info.window_name = TEXT("GDI_Game");
	window_info.width = 800;
	window_info.height = 600;
	window_info.cmd_show = nCmdShow;

	rc = InitializeWindow(window_info);
	if (rc != ResultCode::OK)
	{
		DebugLog("InitializeWindow() fail - WinMain()");

		return 0;
	}

	Game game;
	rc = game.Initialize(window_info.hwnd, window_info.width, window_info.height);
	if (rc != ResultCode::OK)
	{
		DebugLog("Game::Initialize() fail - WinMain()");

		game.Shutdown();

		return 0;
	}

	MyTime::GetInstance().Initialize();

	MSG msg = {};

	while (game.IsRunning())
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		MyTime::GetInstance().Update();

		game.Update();
		game.Render();

		DisplayFPS(MyTime::GetInstance().DeltaTime());
	}

	game.Shutdown();

	DUMP_LEAKS();

	return (int)msg.wParam;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

static ResultCode InitializeWindow(WindowInfo& window_info)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = window_info.hinstance;
	wc.lpszClassName = window_info.class_name;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 기본 커서 모양
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 기본 아이콘 모양
	ATOM result = RegisterClass(&wc);
	if (result == 0)
	{
		DebugLog("RegisterClass() fail - InitializeWindow()");

		return ResultCode::FAIL;
	}

	// 창 크기 딱 맞게 조정
	RECT rcClient = { 0, 0, (LONG)window_info.width, (LONG)window_info.height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 생성
	window_info.hwnd = CreateWindow(
		window_info.class_name,			// 윈도우 클래스 이름
		window_info.window_name,		// 창 제목
		WS_OVERLAPPEDWINDOW,			// 윈도우 스타일
		CW_USEDEFAULT,					// 윈도우 위치 x
		CW_USEDEFAULT,					// 윈도우 위치 y
		rcClient.right - rcClient.left,	// 윈도우 크기 x
		rcClient.bottom - rcClient.top, // 윈도우 크기 y
		NULL,							// 부모 윈도우
		NULL,							// 메뉴
		window_info.hinstance,
		NULL);

	if (window_info.hwnd == nullptr)
	{
		DebugLog("CreateWindow() fail - InitializeWindow()");

		return ResultCode::FAIL;
	}

	ShowWindow(window_info.hwnd, window_info.cmd_show);

	UpdateWindow(window_info.hwnd);

	return ResultCode::OK;
}