#include "../include/display.h"

Display_t::Display_t(Window_t *window_)
{
    window = window_;
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
            if (pixel)
            {
                window->setPixel();
            }
            else
            {
                window->clearPixel();
            }

            window->fill(i, j);
        }
    }
    window->update();
}

bool Display_t::check(uint8_t x_, uint8_t y_)
{
    return display[x_][y_];
}

void Display_t::clear()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            display[i][j] = false;
        }
    }
    window->clear();
}
