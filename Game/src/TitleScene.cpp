#include "TitleScene.h"

#include "DebugUtility.h"
#include "GDIRenderer.h"
#include "ResultCode.h"

TitleScene::TitleScene()
{
	DebugLog("TitleScene »ý¼ºµÊ");
}

TitleScene::~TitleScene()
{
	DebugLog("TitleScene ¼Ò¸êµÊ");
}

ResultCode TitleScene::Initialize()
{
	DebugLog("TitleScene::Initialize()");

	return RESULT_OK;
}

void TitleScene::Update(float delta_time)
{
}

void TitleScene::Render(GDIRenderer& renderer)
{
}

void TitleScene::Shutdown()
{
}
