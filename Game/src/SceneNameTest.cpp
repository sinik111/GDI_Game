#include "SceneNameTest.h"

#include "GDIRenderer.h"

SceneNameTest::SceneNameTest(Gdiplus::Bitmap* image)
	: image(image)
{
}

SceneNameTest::~SceneNameTest()
{
}

void SceneNameTest::Initialize()
{
	
}

void SceneNameTest::Destroy()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
}

void SceneNameTest::Update(float delta_time)
{
}

void SceneNameTest::Render(const GDIRenderer& renderer)
{
	Gdiplus::Rect dst_rect = {};
	Gdiplus::Rect src_rect = {};

	dst_rect.X = 0;
	dst_rect.Y = 0;
	dst_rect.Width = renderer.GetWidth();
	dst_rect.Height = renderer.GetHeight();

	src_rect.X = 0;
	src_rect.Y = 0;
	src_rect.Width = image->GetWidth();
	src_rect.Height = image->GetHeight();

	renderer.DrawImage(image, dst_rect, src_rect);
}
