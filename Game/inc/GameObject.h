#pragma once

class GDIRenderer;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

public:
	virtual void Update(float delta_time) = 0;
	virtual void Render(GDIRenderer& renderer) = 0;
	virtual void Destroy() = 0;
};