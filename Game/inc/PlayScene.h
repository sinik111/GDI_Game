#pragma once

#include "Scene.h"

class GameObject;
struct InitContext;
struct UpdateContext;
enum class ResultCode;

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
	void Update() override;
	void Render() override;
};