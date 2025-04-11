#include "SceneManager.h"

#include "ResultCode.h"
#include "DebugUtility.h"
#include "TitleScene.h"
#include "PlayScene.h"

SceneManager::SceneManager()
	: current_state(SceneState::None), next_state(SceneState::None), current_scene(nullptr)
{
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;

	return instance;
}

void SceneManager::Shutdown()
{
	if (current_scene != nullptr)
	{
		current_scene->Shutdown();

		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::UpdateScene()
{
	ResultCode rc = CheckSceneState();
	if (rc != ResultCode::OK)
	{
		DebugLog("Scene::CheckSceneState() fail - SceneManager::UpdateScene()");
	}

	current_scene->Update();
}

void SceneManager::RenderScene()
{
	current_scene->Render();
}

void SceneManager::ChangeScene(SceneState scene_state)
{
	next_state = scene_state;
}

ResultCode SceneManager::CheckSceneState()
{
	if (current_state != next_state)
	{
		ResultCode rc = CreateScene();
		if (rc != ResultCode::OK)
		{
			DebugLog("SceneManager::CreateScene() fail - SceneManager::CheckSceneState()");

			next_state = current_state;

			return ResultCode::FAIL;
		}

		current_state = next_state;
	}

	return ResultCode::OK;
}

ResultCode SceneManager::CreateScene()
{
	Scene* new_scene = nullptr;

	switch (next_state)
	{
	case SceneState::Title:
		new_scene = new TitleScene();
		break;

	case SceneState::Play:
		new_scene = new PlayScene();
		break;
	}

	ResultCode rc = new_scene->Initialize();
	if (rc != ResultCode::OK)
	{
		DebugLog("Scene::Initialize() fail - SceneManager::CreateScene()");

		new_scene->Shutdown();

		delete new_scene;

		return ResultCode::FAIL;
	}

	if (current_scene != nullptr)
	{
		current_scene->Shutdown();
		delete current_scene;
	}

	current_scene = new_scene;

	return ResultCode::OK;
}