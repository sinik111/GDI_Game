#include "DebugUtility.h"

#ifdef _DEBUG

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include <string>
#include <iostream>

static bool use_console = false;

// 콘솔 초기화
void __InitializeConsole()
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    SetConsoleTitle(L"윈도우 메시지 콘솔 로그");
    use_console = true;

    DebugLog("콘솔 로그 시작...");
}

void __ReleaseConsole()
{
    // 표준 출력 스트림 닫기
    fclose(stdout);
    // 콘솔 해제
    FreeConsole();
}

// FPS 출력
static int frame_count = 0;
static float frame_timer = 0.0f;
static char fps_buffer[30] = { 0 };

void __DisplayFPS(float delta_time)
{
    ++frame_count;

    frame_timer += delta_time;
    if (frame_timer > 1.0f)
    {
        memset(fps_buffer, 0, sizeof(fps_buffer));
        sprintf_s(fps_buffer, 30, "FPS: %d", frame_count);

        frame_timer -= 1.0f;
        frame_count = 0;

        DebugLog(fps_buffer);
    }
}

// 로그 출력
void __PrintDebugLog(const std::string& log)
{
    std::string out = log + "\n";
    OutputDebugStringA(out.c_str());

    if (use_console)
    {
        std::cout << out;
    }
}

void __PrintDebugLog(const std::wstring& log)
{
    std::wstring out = log + L"\n";
    OutputDebugStringW(out.c_str());

    if (use_console)
    {
        std::wcout << out;
    }
}

void __PrintDebugLog(const char* fmt, ...)
{
    char buffer[1024];

    va_list args;

    va_start(args, fmt);

    vsnprintf_s(buffer, 1024, _TRUNCATE, fmt, args);

    va_end(args);

    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");

    if (use_console)
    {
        printf("%s\n", buffer);
    }
}

void __PrintDebugLog(const wchar_t* fmt, ...)
{
    wchar_t buffer[1024];

    va_list args;

    va_start(args, fmt);

    _vsnwprintf_s(buffer, 1024, _TRUNCATE, fmt, args);

    va_end(args);

    OutputDebugStringW(buffer);
    OutputDebugStringW(L"\n");

    if (use_console)
    {
        wprintf(L"%s\n", buffer);

    }
}

#endif // _DEBUG