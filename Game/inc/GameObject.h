#pragma once

class GDIRenderer;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

public:
	virtual void Initialize() = 0;
	virtual void Destroy() = 0;

public:
	virtual void Update() = 0;
	virtual void Render(const GDIRenderer&) = 0;
};