#pragma once

#include "Scene.h"

class GameObject;
enum ResultCode;

class PlayScene : public Scene
{
private:
	GameObject* object;

public:
	PlayScene();
	~PlayScene();

public:
	ResultCode Initialize() override;
	void Shutdown() override;

public:
	void Update(float delta_time) override;
	void Render(const GDIRenderer& renderer) override;
};