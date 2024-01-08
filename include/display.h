#pragma once
#include <functional>
#include "../include/window.h"

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

#define WIDTH 64
#define HEIGHT 32
#define SCALE 20

class Display_t
{
private:
    Window_t *window;
    bool display[WIDTH][HEIGHT] = {0};
    SDL_Event e;

public:
    Display_t(Window_t *window_);
    ~Display_t();
    void drawPixel(uint8_t x_, uint8_t y_);
    void clearPixel(uint8_t x_, uint8_t y_);
    bool check(uint8_t x_, uint8_t y_);
    void update();
    void clear();
};