#include "TitleScene.h"

#include "DebugUtility.h"
#include "ResultCode.h"
#include "SceneNameTest.h"
#include "FileLoader.h"
#include "Input.h"
#include "SceneManager.h"
#include "GDIRenderer.h"

TitleScene::TitleScene()
	: object(nullptr)
{
	DebugLog("TitleScene »ý¼ºµÊ");
}

TitleScene::~TitleScene()
{
	DebugLog("TitleScene ¼Ò¸êµÊ");
	if (object != nullptr)
	{
		delete object;
		object = nullptr;
	}
}

ResultCode TitleScene::Initialize()
{
	DebugLog("TitleScene::Initialize()");

	Gdiplus::Bitmap* image = FileLoader::GetInstance().LoadImageFile(L"image/title.png");
	if (image == nullptr)
	{
		DebugLog("FileLoader::LoadImageFile() fail TitleScene::Initialize()");

		return ResultCode::FAIL;
	}
	object = new SceneNameTest(image);

	return ResultCode::OK;
}

void TitleScene::Update()
{
	if (Input::GetInstance().IsKeyReleased('A'))
	{
		SceneManager::GetInstance().ChangeScene(SceneState::Play);
	}

	object->Update();
}

void TitleScene::Render()
{
	object->Render(GDIRenderer::GetInstance());
}

void TitleScene::Shutdown()
{
	
}
