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

class Window_t
{
private:
    inline static SDL_Window *window;
    inline static SDL_Renderer *renderer;
    SDL_Event e;

public:
    Window_t();
    ~Window_t();
    void setPixel();
    void clearPixel();
    void fill(const int &x, const int &y);
    void update();
    void start();
    void clear();
    void destroy();
    bool poll();
};