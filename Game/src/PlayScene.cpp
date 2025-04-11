#include "PlayScene.h"

#include "DebugUtility.h"
#include "ResultCode.h"
#include "FileLoader.h"
#include "SceneNameTest.h"
#include "Input.h"
#include "SceneManager.h"
#include "GDIRenderer.h"

PlayScene::PlayScene()
	: object(nullptr)
{
	DebugLog("PlayScene »ý¼ºµÊ");
}

PlayScene::~PlayScene()
{
	DebugLog("PlayScene ¼Ò¸êµÊ");

	if (object != nullptr)
	{
		delete object;
		object = nullptr;
	}
}

ResultCode PlayScene::Initialize()
{
	DebugLog("PlayScene::Initialize()");

	Gdiplus::Bitmap* image = FileLoader::GetInstance().LoadImageFile(L"image/play.png");
	if (image == nullptr)
	{
		DebugLog("FileLoader::LoadImageFile() fail PlayScene::Initialize()");

		return ResultCode::FAIL;
	}

	object = new SceneNameTest(image);

	return ResultCode::OK;
}

void PlayScene::Update()
{
	if (Input::GetInstance().IsKeyReleased('1'))
	{
		SceneManager::GetInstance().ChangeScene(SceneState::Title);
	}
}

void PlayScene::Render()
{
	object->Render(GDIRenderer::GetInstance());
}

void PlayScene::Shutdown()
{
}
