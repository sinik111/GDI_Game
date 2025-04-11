#pragma once

#include <windows.h>

class SceneManager;
class GDIRenderer;
class FileLoader;
class Input;

enum class ResultCode;

class Game
{
private:
	bool is_running;

public: // 생성자, 소멸자
	Game();
	~Game();

public: // 초기화, 정리
	ResultCode Initialize(HWND hWnd, int width, int height);
	void Shutdown();

public: // 루프
	void Update();
	void Render();

public:
	bool IsRunning();
};
