#pragma once

class GDIRenderer;
enum ResultCode;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	virtual ResultCode Initialize() = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render(GDIRenderer& renderer) = 0;
	virtual void Shutdown() = 0;
};