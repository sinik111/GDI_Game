#pragma once

#include "Scene.h"

class GameObject;
struct InitContext;
struct UpdateContext;
enum ResultCode;

class PlayScene : public Scene
{
private:
	GameObject* object;

public:
	PlayScene();
	~PlayScene();

public:
	ResultCode Initialize(const InitContext& init_context) override;
	void Shutdown() override;

public:
	void Update(const UpdateContext& update_context) override;
	void Render(const GDIRenderer& renderer) override;
};