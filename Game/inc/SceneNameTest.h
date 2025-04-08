#pragma once

#include "GameObject.h"

namespace Gdiplus
{
	class Bitmap;
}

class GDIRenderer;

class SceneNameTest : public GameObject
{
private:
	Gdiplus::Bitmap* image;

public:
	SceneNameTest(Gdiplus::Bitmap* image);
	virtual ~SceneNameTest();

public: // 초기화, 정리
	void Initialize() override;
	void Destroy() override;

public: // 루프
	void Update(float delta_time) override;
	void Render(const GDIRenderer& renderer) override;
};