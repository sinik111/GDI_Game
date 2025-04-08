#pragma once

#include "Scene.h"

enum ResultCode;
class GameObject;

class TitleScene : public Scene
{
private:
	GameObject* object;

public:
	TitleScene();
	~TitleScene();

public:
	ResultCode Initialize() override;
	void Shutdown() override;

public:
	void Update(float delta_time) override;
	void Render(const GDIRenderer& renderer) override;
};