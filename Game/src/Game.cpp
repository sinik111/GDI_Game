#include "Game.h"

#include <windows.h>

#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Input.h"
#include "GDIRenderer.h"
#include "DebugUtility.h"
#include "ResultCode.h"
#include "FileLoader.h"
#include "Contexts.h"

Game::Game()
	: gdi_renderer(nullptr), file_loader(nullptr), scene(nullptr),
	current_scene_state(SceneState::None), next_scene_state(SceneState::None),
	is_running(false)
{
	DebugLog("Game 积己凳");
}

ResultCode Game::Initialize(HWND hwnd, int width, int height)
{
	DebugLog("Game::Initialize()");

	ResultCode rc = RESULT_OK;

	// Game 林夸 葛碘 积己

	gdi_renderer = new GDIRenderer(hwnd, width, height);

	rc = gdi_renderer->Initialize();
	if (rc != RESULT_OK)
	{
		DebugLog("GDIRenderer::Initialize() fail - Game::Initialize()");

		return RESULT_FAIL;
	}

	file_loader = new FileLoader(L"bin", L"resources");

	rc = file_loader->Initialize();
	if (rc != RESULT_OK)
	{
		DebugLog("FileLoader::Initialize() fail - Game::Initialize()");

		return RESULT_FAIL;
	}


	// Title Scene 积己

	next_scene_state = SceneState::Title;

	rc = CreateScene();
	if (rc != RESULT_OK)
	{
		DebugLog("CreateScene() fail - Game::Initialize()");

		return RESULT_FAIL;
	}

	current_scene_state = next_scene_state;

	is_running = true;

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

	if (file_loader != nullptr)
	{
		delete file_loader;
		file_loader = nullptr;
	}
}

// game loop ---

void Game::Update(float delta_time)
{
	if (Input::GetInstance().IsKeyReleased('A'))
	{
		ChangeScene(SceneState::Play);
	}

	if (Input::GetInstance().IsKeyReleased('B'))
	{
		ChangeScene(SceneState::Title);
	}

	if (Input::GetInstance().IsKeyReleased(VK_ESCAPE))
	{
		is_running = false;
	}

	CheckSceneState();

	if (!is_running)
	{
		return;
	}

	UpdateContext update_context;
	update_context.file_loader = file_loader;

	scene->Update(update_context);
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

ResultCode Game::CreateScene()
{
	if (scene != nullptr)
	{
		scene->Shutdown();

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

	InitContext init_context;
	init_context.file_loader = file_loader;

	ResultCode rc = scene->Initialize(init_context);
	if (rc != RESULT_OK)
	{
		DebugLog("Scene::Initialize() fail - Game::CreateScene()");

		scene->Shutdown();

		delete scene;
		scene = nullptr;

		is_running = false;

		return RESULT_FAIL;
	}

	return RESULT_OK;
}
