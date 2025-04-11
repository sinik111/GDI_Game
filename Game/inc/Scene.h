#pragma once

enum class ResultCode;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	virtual ResultCode Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
};