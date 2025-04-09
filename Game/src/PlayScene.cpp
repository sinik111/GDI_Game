#include "PlayScene.h"

#include "DebugUtility.h"
#include "GDIRenderer.h"
#include "ResultCode.h"
#include "FileLoader.h"
#include "SceneNameTest.h"
#include "Contexts.h"

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

ResultCode PlayScene::Initialize(const InitContext& init_context)
{
	DebugLog("PlayScene::Initialize()");

	Gdiplus::Bitmap* image = init_context.file_loader->LoadImageFile(L"image/play.png");
	if (image == nullptr)
	{
		DebugLog("FileLoader::LoadImageFile() fail PlayScene::Initialize()");

		return RESULT_FAIL;
	}

	object = new SceneNameTest(image);

	return RESULT_OK;
}

void PlayScene::Update(const UpdateContext& update_context)
{
}

void PlayScene::Render(const GDIRenderer& renderer)
{
	object->Render(renderer);
}

void PlayScene::Shutdown()
{
}
