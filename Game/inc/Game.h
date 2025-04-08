#pragma once

#include <windows.h>

enum class SceneState
{
	None,
	Title,
	Play
};

class Scene;
class GDIRenderer;
enum ResultCode;

class Game
{
private:
	// Renderer
	GDIRenderer* gdi_renderer;

	// 씬 관련 변수들
	Scene* scene;

	SceneState current_scene_state;
	SceneState next_scene_state;

	// 게임 종료
	bool is_running;

public: // 생성자, 소멸자
	Game();
	~Game() = default;

public: // 초기화, 정리
	ResultCode Initialize(HWND hWnd, int width, int height);
	void Shutdown();

public: // 루프
	void Update(float delta_time);
	void Render();

public:
	bool IsRunning();

public:
	void ChangeScene(SceneState new_scene);

private:
	void CheckSceneState();
	void CreateScene();
};