#pragma once

class Scene;
class FileLoader;
class Input;

struct InitContext
{
	FileLoader* file_loader;
};

struct UpdateContext
{
	Input* input;
	Scene* scene;
	FileLoader* file_loader;
	float delta_time;
};