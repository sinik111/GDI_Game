#include "Input.h"

#include <windows.h> // GetAsyncKeyState »ç¿ë
#include <memory>

static short current_key_state[256] = { 0 };
static short previous_key_state[256] = { 0 };

void Input::Update()
{
    memcpy_s(previous_key_state, sizeof(previous_key_state), current_key_state, sizeof(current_key_state));

    for (int i = 0; i < 256; ++i)
    {
        current_key_state[i] = GetAsyncKeyState(i);
    }
}

bool Input::IsKeyDown(int vkey)
{
    return (current_key_state[vkey] & 0x8000) != 0;
}

bool Input::IsKeyPressed(int vkey)
{
    return (!(previous_key_state[vkey] & 0x8000) && (current_key_state[vkey] & 0x8000));
}

bool Input::IsKeyReleased(int vkey)
{
    return ((previous_key_state[vkey] & 0x8000) && !(current_key_state[vkey] & 0x8000));
}