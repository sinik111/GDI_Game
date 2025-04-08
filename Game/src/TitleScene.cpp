#include "TitleScene.h"

#include "DebugUtility.h"
#include "GDIRenderer.h"
#include "ResultCode.h"
#include "SceneNameTest.h"
#include "FileLoader.h"

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

		return RESULT_FAIL;
	}
	object = new SceneNameTest(image);

	return RESULT_OK;
}

void TitleScene::Update(float delta_time)
{
	object->Update(delta_time);
}

void TitleScene::Render(const GDIRenderer& renderer)
{
	object->Render(renderer);
}

void TitleScene::Shutdown()
{
	
}
