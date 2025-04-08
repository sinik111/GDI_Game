#include "Game.h"

#include <windows.h>

#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Input.h"
#include "GDIRenderer.h"
#include "DebugUtility.h"
#include "ResultCode.h"

Game::Game()
	: gdi_renderer(nullptr), scene(nullptr),
	current_scene_state(SceneState::None), next_scene_state(SceneState::None),
	is_running(true)
{
	DebugLog("Game 생성됨");
}

ResultCode Game::Initialize(HWND hwnd, int width, int height)
{
	DebugLog("Game::Initialize()");

	ResultCode rc = RESULT_OK;

	gdi_renderer = new GDIRenderer(hwnd, width, height);
	if (gdi_renderer == nullptr)
	{
		DebugLog("GDIRenderer 할당 실패 - Game::Initialize()");

		return RESULT_FAIL;
	}

	rc = gdi_renderer->Initialize();
	if (rc != RESULT_OK)
	{
		DebugLog("GDIRenderer::Initialize() 실패 - Game::Initialize()");

		return RESULT_FAIL;
	}

	next_scene_state = SceneState::Title;

	scene = new TitleScene();
	if (scene == nullptr)
	{
		DebugLog("Scene 할당 실패 - Game::Initialize()");

		return RESULT_FAIL;
	}

	rc = scene->Initialize();
	if (rc != RESULT_OK)
	{
		DebugLog("Scene::Initialize() 실패 - Game::Initialize()");

		return RESULT_FAIL;
	}

	current_scene_state = next_scene_state;

	return RESULT_OK;
}

void Game::Shutdown()
{
	DebugLog("Game::Shutdown()");

	if (scene != nullptr)
	{
		scene->Shutdown();
		delete scene;
		scene = nullptr;
	}

	if (gdi_renderer != nullptr)
	{
		gdi_renderer->Shutdown();
		delete gdi_renderer;
		gdi_renderer = nullptr;
	}
}

// game loop ---

void Game::Update(float delta_time)
{
	CheckSceneState();

	scene->Update(delta_time);

	if (Input::IsKeyReleased('A'))
	{
		ChangeScene(SceneState::Play);
	}

	if (Input::IsKeyReleased('B'))
	{
		ChangeScene(SceneState::Title);
	}

	if (Input::IsKeyReleased(VK_ESCAPE))
	{
		is_running = false;
	}

	Input::Update();
}

void Game::Render()
{
	gdi_renderer->BeginDraw();

	scene->Render(*gdi_renderer);

	gdi_renderer->EndDraw();
}

// --- --- ---

bool Game::IsRunning()
{
	return is_running;
}

void Game::ChangeScene(SceneState new_scene)
{
	next_scene_state = new_scene;
}

void Game::CheckSceneState()
{
	if (current_scene_state != next_scene_state)
	{
		CreateScene();

		current_scene_state = next_scene_state;
	}
}

void Game::CreateScene()
{
	if (scene != nullptr)
	{
		delete scene;
		scene = nullptr;
	}

	switch (next_scene_state)
	{
	case SceneState::Title:
		scene = new TitleScene();
		break;

	case SceneState::Play:
		scene = new PlayScene();
		break;
	}

	scene->Initialize();
}
