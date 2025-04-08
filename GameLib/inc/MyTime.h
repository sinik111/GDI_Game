#pragma once

#include <windows.h>

class MyTime
{
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER current_counter;
	LARGE_INTEGER previous_counter;

	float delta_time;

public:
	MyTime();

public:
	void Initialize();
	void Update();
	float DeltaTime();
};