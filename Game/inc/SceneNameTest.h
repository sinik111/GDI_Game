#pragma once

#include "GameObject.h"

namespace Gdiplus
{
	class Bitmap;
}

class SceneNameTest : public GameObject
{
private:
	Gdiplus::Bitmap* image;
	int id;

public:
	SceneNameTest(int id);
	virtual ~SceneNameTest();

public: // 초기화, 정리
	void Initialize() override;
	void Destroy() override;

public: // 루프
	void Update() override;
	void Render(const GDIRenderer& renderer) override;
};