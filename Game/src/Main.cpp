#include <windows.h>

#include "MyTime.h"
#include "DebugUtility.h"
#include "Game.h"
#include "ResultCode.h"

static HWND g_hWnd = NULL;

const int g_width = 800;
const int g_height = 600;

static LPCTSTR szClassName = TEXT("GDI");

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void InitializeWindow(HINSTANCE hInstance);

// main
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ENABLE_LEAK_CHECK();

	InitializeConsole();

	InitializeWindow(hInstance);

	ShowWindow(g_hWnd, nCmdShow);

	UpdateWindow(g_hWnd);


	Game game;
	ResultCode rc = game.Initialize(g_hWnd, g_width, g_height);
	if (rc != RESULT_OK)
	{
		DebugLog("game.Initialize() fail - WinMain()");

		game.Shutdown();

		ReleaseConsole();

		DUMP_LEAKS();

		return 0;
	}

	MyTime my_time;
	my_time.Initialize();

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

		float delta_time = my_time.DeltaTime();

		game.Update(delta_time);

		if (!game.IsRunning())
		{
			break;
		}

		game.Render();

		CHECK_FPS(delta_time);

		my_time.Update();
	}

	game.Shutdown();

	ReleaseConsole();

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

static void InitializeWindow(HINSTANCE hInstance)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = szClassName;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 기본 커서 모양
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 기본 아이콘 모양
	RegisterClass(&wc);

	// 창 크기 딱 맞게 조정
	RECT rcClient = { 0, 0, (LONG)g_width, (LONG)g_height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 생성
	g_hWnd = CreateWindow(
		szClassName,					// 윈도우 클래스 이름
		TEXT("GDI_Game"),				// 창 제목
		WS_OVERLAPPEDWINDOW,			// 윈도우 스타일
		800,							// 윈도우 위치 x
		500,							// 윈도우 위치 y
		rcClient.right - rcClient.left,	// 윈도우 크기 x
		rcClient.bottom - rcClient.top, // 윈도우 크기 y
		NULL,							// 부모 윈도우
		NULL,							// 메뉴
		hInstance,
		NULL);
}