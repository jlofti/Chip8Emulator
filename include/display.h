#pragma once
#include <functional>

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
    inline static SDL_Window *window;
    inline static SDL_Renderer *renderer;
    bool display[WIDTH][HEIGHT] = {0};
    SDL_Event e;

public:
    Display_t();
    ~Display_t();
    void start();
    void clear();
    void drawPixel(uint8_t x_, uint8_t y_);
    void clearPixel(uint8_t x_, uint8_t y_);
    bool check(uint8_t x_, uint8_t y_);
    void update();
    void destroy();
    bool poll();
};