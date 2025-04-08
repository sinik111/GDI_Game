#pragma once

#include "Scene.h"

enum ResultCode;

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

public:
	ResultCode Initialize() override;
	void Update(float delta_time) override;
	void Render(GDIRenderer& renderer) override;
	void Shutdown() override;
};