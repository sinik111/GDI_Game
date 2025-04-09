#include "TitleScene.h"

#include "DebugUtility.h"
#include "GDIRenderer.h"
#include "ResultCode.h"
#include "SceneNameTest.h"
#include "FileLoader.h"
#include "Contexts.h"

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

ResultCode TitleScene::Initialize(const InitContext& init_context)
{
	DebugLog("TitleScene::Initialize()");

	Gdiplus::Bitmap* image = init_context.file_loader->LoadImageFile(L"image/title.png");
	if (image == nullptr)
	{
		DebugLog("FileLoader::LoadImageFile() fail TitleScene::Initialize()");

		return RESULT_FAIL;
	}
	object = new SceneNameTest(image);

	return RESULT_OK;
}

void TitleScene::Update(const UpdateContext& update_context)
{
	object->Update(update_context.delta_time);
}

void TitleScene::Render(const GDIRenderer& renderer)
{
	object->Render(renderer);
}

void TitleScene::Shutdown()
{
	
}
