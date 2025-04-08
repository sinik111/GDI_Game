#include "PlayScene.h"

#include "DebugUtility.h"
#include "GDIRenderer.h"
#include "ResultCode.h"
#include "FileLoader.h"
#include "SceneNameTest.h"

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

	DebugLog("TitleScene::Initialize()");

	Gdiplus::Bitmap* image = FileLoader::GetInstance().LoadImageFile(L"image/play.png");
	if (image == nullptr)
	{
		DebugLog("FileLoader::LoadImageFile() fail PlayScene::Initialize()");

		return RESULT_FAIL;
	}

	object = new SceneNameTest(image);

	return RESULT_OK;
}

void PlayScene::Update(float delta_time)
{
}

void PlayScene::Render(const GDIRenderer& renderer)
{
	object->Render(renderer);
}

void PlayScene::Shutdown()
{
}
