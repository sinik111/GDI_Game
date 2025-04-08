#include "PlayScene.h"

#include "DebugUtility.h"
#include "GDIRenderer.h"
#include "ResultCode.h"

PlayScene::PlayScene()
{
	DebugLog("PlayScene »ý¼ºµÊ");
}

PlayScene::~PlayScene()
{
	DebugLog("PlayScene ¼Ò¸êµÊ");
}

ResultCode PlayScene::Initialize()
{
	DebugLog("PlayScene::Initialize()");

	return RESULT_OK;
}

void PlayScene::Update(float delta_time)
{
}

void PlayScene::Render(GDIRenderer& renderer)
{
}

void PlayScene::Shutdown()
{
}
