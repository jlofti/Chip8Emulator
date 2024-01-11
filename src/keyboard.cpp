#include "../include/keyboard.h"

Keyboard_t::Keyboard_t()
{
}

Keyboard_t::~Keyboard_t()
{
}
bool Keyboard_t::getKey(const uint8_t &key_)
{
    return keys[key_];
}

void Keyboard_t::keyUp(const uint8_t &key_)
{
    keys[key_] = false;
}

void Keyboard_t::keyDown(const uint8_t &key_)
{
    keys[key_] = true;
}

uint8_t Keyboard_t::scanCodeToKey(const SDL_Scancode &scancode_)
{
    return scanToKey[scancode_];
}

bool Keyboard_t::validKey(const SDL_Scancode &scancode_)
{
    return scanToKey.count(scancode_);
}
