#pragma once

#include "Scene.h"

enum ResultCode;

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

public:
	ResultCode Initialize() override;
	void Update(float delta_time) override;
	void Render(GDIRenderer& renderer) override;
	void Shutdown() override;
};