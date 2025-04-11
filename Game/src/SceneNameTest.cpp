#include "SceneNameTest.h"

#include "GDIRenderer.h"
#include "Resources.h"

SceneNameTest::SceneNameTest(int id)
	:image(nullptr), id(id)
{
}

SceneNameTest::~SceneNameTest()
{
}

void SceneNameTest::Initialize()
{
	if (id == 0)
	{
		image = Resources::GetInstance().GetImage("title_image", ResourceGroup::Title);
	}
	else
	{
		image = Resources::GetInstance().GetImage("play_image", ResourceGroup::Play);
	}
}

void SceneNameTest::Destroy()
{

}

void SceneNameTest::Update()
{
}

void SceneNameTest::Render(const GDIRenderer& renderer)
{
	Gdiplus::Rect dst_rect = {};
	Gdiplus::Rect src_rect = {};

	dst_rect.X = 0;
	dst_rect.Y = 0;
	dst_rect.Width = GDIRenderer::GetInstance().GetWidth();
	dst_rect.Height = GDIRenderer::GetInstance().GetHeight();

	src_rect.X = 0;
	src_rect.Y = 0;
	src_rect.Width = image->GetWidth();
	src_rect.Height = image->GetHeight();

	renderer.DrawImage(image, dst_rect, src_rect);
}
