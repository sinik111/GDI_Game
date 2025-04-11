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
#include "SceneManager.h"

Game::Game()
	: is_running(false)
{
	DebugLog("Game »ý¼ºµÊ");
}

Game::~Game()
{
	DebugLog("Game ¼Ò¸êµÊ");
}

ResultCode Game::Initialize(HWND hwnd, int width, int height)
{
	DebugLog("Game::Initialize()");

	ResultCode rc = ResultCode::OK;

	rc = GDIRenderer::GetInstance().Initialize(hwnd, width, height);
	if (rc != ResultCode::OK)
	{
		DebugLog("GDIRenderer::Initialize() fail - Game::Initialize()");

		return ResultCode::FAIL;
	}

	rc = FileLoader::GetInstance().Initialize(L"bin", L"resources");
	if (rc != ResultCode::OK)
	{
		DebugLog("FileLoader::Initialize() fail - Game::Initialize()");

		return ResultCode::FAIL;
	}

	SceneManager::GetInstance().ChangeScene(SceneState::Title);
	rc = SceneManager::GetInstance().CheckSceneState();
	if (rc != ResultCode::OK)
	{
		DebugLog("SceneManager::CheckSceneState() fail - Game::Initialize()");

		return ResultCode::FAIL;
	}

	is_running = true;

	return ResultCode::OK;
}

void Game::Shutdown()
{
	DebugLog("Game::Shutdown()");

	GDIRenderer::GetInstance().Shutdown();
	SceneManager::GetInstance().Shutdown();
}

// game loop ---

void Game::Update()
{
	Input::GetInstance().Update();

	if (Input::GetInstance().IsKeyReleased(VK_ESCAPE))
	{
		is_running = false;
	}

	SceneManager::GetInstance().UpdateScene();
}

void Game::Render()
{
	GDIRenderer::GetInstance().BeginDraw();

	SceneManager::GetInstance().RenderScene();

	GDIRenderer::GetInstance().EndDraw();
}

// --- --- ---

bool Game::IsRunning()
{
	return is_running;
}