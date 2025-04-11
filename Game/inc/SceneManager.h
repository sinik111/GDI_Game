#pragma once

class Scene;

enum class ResultCode;
enum class SceneState
{
	None,
	Title,
	Play
};

class SceneManager
{
private:
	SceneState current_state;
	SceneState next_state;

	Scene* current_scene;

private:
	SceneManager();

public:
	static SceneManager& GetInstance();

public:
	void Shutdown();

public:
	void UpdateScene();
	void RenderScene();

public:
	void ChangeScene(SceneState scene_state);
	ResultCode CheckSceneState();

private:
	ResultCode CreateScene();
};