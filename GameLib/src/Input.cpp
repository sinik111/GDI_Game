#include "Input.h"

#include <windows.h> // GetAsyncKeyState »ç¿ë
#include <memory>

Input::Input()
{
    memset(current_key_state, 0, sizeof(current_key_state));
    memset(previous_key_state, 0, sizeof(previous_key_state));
}

Input& Input::GetInstance()
{
    static Input instance;

    return instance;
}

void Input::Update()
{
    memcpy_s(previous_key_state, sizeof(previous_key_state), current_key_state, sizeof(current_key_state));

    for (int i = 0; i < 256; ++i)
    {
        current_key_state[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }
}

bool Input::IsKeyDown(int vkey)
{
    return current_key_state[vkey];
}

bool Input::IsKeyPressed(int vkey)
{
    return (!previous_key_state[vkey] && current_key_state[vkey]);
}

bool Input::IsKeyReleased(int vkey)
{
    return (previous_key_state[vkey] && !current_key_state[vkey]);
}