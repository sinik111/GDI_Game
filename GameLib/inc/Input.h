#pragma once

class Input
{
private:
	bool current_key_state[256];
	bool previous_key_state[256];

private:
	Input();
	Input(const Input&) = delete;

public:
	static Input& GetInstance();

	// 매 루프마다 호출 필요
	void Update();

	// 키가 눌려진 상태인지 확인
	bool IsKeyDown(int vkey);

	// 이번 루프에 키가 눌려졌는지 확인
	bool IsKeyPressed(int vkey);

	// 이번 루프에 키가 놓아졌는지 확인
	bool IsKeyReleased(int vkey);
};