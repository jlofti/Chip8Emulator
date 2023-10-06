#include "../include/display.h"

void Display_t::start()
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

Display_t::Display_t()
{
}

void Display_t::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Display_t::clearPixel(uint8_t x_, uint8_t y_)
{
    display[x_][y_] = 0;
}

void Display_t::drawPixel(uint8_t x_, uint8_t y_)
{
    display[x_][y_] = 1;
}

void Display_t::update()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            bool pixel = display[i][j];
            SDL_Rect rect;
            rect.x = i * SCALE;
            rect.y = j * SCALE;
            rect.w = 1 * SCALE;
            rect.h = 1 * SCALE;
            if (pixel)
            {
                printf("Draw pixel at : %d, %d\n", i, j);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else
            {
                printf("Clear pixel at : %d, %d\n", i, j);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    printf("Display updated\n");
}

bool Display_t::check(uint8_t x_, uint8_t y_)
{
    return display[x_][y_];
}

void Display_t::destroy()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display_t::poll()
{
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT)
    {
        return 0;
    }
    return 1;
}