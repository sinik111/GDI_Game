#include "MyTime.h"

#include <windows.h>

MyTime::MyTime()
	: frequency({}), current_counter({}), previous_counter({}), delta_time(0.0f)
{
	
}

MyTime& MyTime::GetInstance()
{
	static MyTime instance;

	return instance;
}

void MyTime::Initialize()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previous_counter);
}

void MyTime::Update()
{
	QueryPerformanceCounter(&current_counter);

	delta_time = (float)(current_counter.QuadPart - previous_counter.QuadPart) / frequency.QuadPart;

	previous_counter = current_counter;
}

float MyTime::DeltaTime()
{
	return delta_time;
}