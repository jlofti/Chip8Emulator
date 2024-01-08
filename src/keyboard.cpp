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
    printf("Up %d\n", key_);
    keys[key_] = false;
}

void Keyboard_t::keyDown(const uint8_t &key_)
{
    printf("Press %d\n", key_);
    keys[key_] = true;
}

uint8_t Keyboard_t::scanCodeToKey(const SDL_Scancode &scancode_)
{

    if (scanToKey.count(scancode_))
    {
        return scanToKey[scancode_];
    }

    /* switch (scancode_)
     {
     case SDL_SCANCODE_1:
         return 0x1;
         break;
     case SDL_SCANCODE_2:
         return 0x2;
         break;
     case SDL_SCANCODE_3:
         return 0x3;
         break;
     case SDL_SCANCODE_4:
         return 0x4;
         break;
     case SDL_SCANCODE_Q:
         return 0x5;
         break;
     case SDL_SCANCODE_W:
         return 0x6;
         break;
     case SDL_SCANCODE_E:
         return 0x7;
         break;
     case SDL_SCANCODE_R:
         return 0x8;
         break;
     case SDL_SCANCODE_A:
         return 0x9;
         break;
     case SDL_SCANCODE_S:
         return 0xA;
         break;
     case SDL_SCANCODE_D:
         return 0xB;
         break;
     case SDL_SCANCODE_F:
         return 0xC;
         break;
     case SDL_SCANCODE_Z:
         return 0xD;
         break;
     case SDL_SCANCODE_X:
         return 0xE;
         break;
     case SDL_SCANCODE_C:
         return 0x0;
         break;
     case SDL_SCANCODE_V:
         return 0xF;
         break;
     }*/
}
