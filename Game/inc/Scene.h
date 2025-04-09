#pragma once

class GDIRenderer;
struct InitContext;
struct UpdateContext;
enum ResultCode;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	virtual ResultCode Initialize(const InitContext& init_context) = 0;
	virtual void Update(const UpdateContext& update_context) = 0;
	virtual void Render(const GDIRenderer& renderer) = 0;
	virtual void Shutdown() = 0;
};