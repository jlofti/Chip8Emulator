#include "../include/window.h"

Window_t::Window_t()
{
}

Window_t::~Window_t()
{
}

void Window_t::start()
{
    // Init SDL Window
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        printf("SDL failed init");
    }

    // Create the window
    SDL_CreateWindowAndRenderer(WIDTH * SCALE, HEIGHT * SCALE, 0, &window, &renderer);

    if (window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        printf("Window failed init");
    }

    SDL_SetWindowTitle(window, "Chip 8 Emulator");
}

void Window_t::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Window_t::destroy()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window_t::poll()
{
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT)
    {
        return 0;
    }
    return 1;
}

void Window_t::setPixel()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Window_t::clearPixel()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Window_t::fill(const int &x, const int &y)
{
    SDL_Rect rect;
    rect.x = x * SCALE;
    rect.y = y * SCALE;
    rect.w = 1 * SCALE;
    rect.h = 1 * SCALE;

    SDL_RenderFillRect(renderer, &rect);
};

void Window_t::update()
{
    SDL_RenderPresent(renderer);
}