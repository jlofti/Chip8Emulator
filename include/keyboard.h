#pragma once
#include <stdint.h>

class Keyboard_t
{
private:
    bool keys[16] = {0};
    uint8_t scanCodeToKey(uint8_t scancode_);

public:
    Keyboard_t();
    ~Keyboard_t();
    uint8_t getKey(uint8_t key_);
    void keyUp(uint8_t key_);
    void keyDown(uint8_t key_);
};