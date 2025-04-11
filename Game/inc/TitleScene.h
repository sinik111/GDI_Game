#pragma once

#include "Scene.h"

class GameObject;
enum class ResultCode;

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
	void Update() override;
	void Render() override;
};