#pragma once

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

#include <stdint.h>
#include <unordered_map>

class Keyboard_t
{
private:
    bool keys[16] = {0};
    std::unordered_map<SDL_Scancode, uint8_t> scanToKey = {
        {SDL_SCANCODE_1, 0x01},
        {SDL_SCANCODE_2, 0x02},
        {SDL_SCANCODE_3, 0x03},
        {SDL_SCANCODE_4, 0x0C},
        {SDL_SCANCODE_Q, 0x04},
        {SDL_SCANCODE_W, 0x05},
        {SDL_SCANCODE_E, 0x06},
        {SDL_SCANCODE_R, 0x0D},
        {SDL_SCANCODE_A, 0x07},
        {SDL_SCANCODE_S, 0x08},
        {SDL_SCANCODE_D, 0x09},
        {SDL_SCANCODE_F, 0x0E},
        {SDL_SCANCODE_Z, 0x0A},
        {SDL_SCANCODE_X, 0x00},
        {SDL_SCANCODE_C, 0x0B},
        {SDL_SCANCODE_V, 0x0F}};

public:
    Keyboard_t();
    ~Keyboard_t();
    uint8_t scanCodeToKey(const SDL_Scancode &scancode_);
    bool getKey(const uint8_t &key_);
    void keyUp(const uint8_t &key__);
    void keyDown(const uint8_t &key_);
};