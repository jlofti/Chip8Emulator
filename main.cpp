#include <iostream>
#include "include/memory.h"
#include "include/cpu.h"
#include "include/display.h"
#include "include/window.h"
#include "include/keyboard.h"

int main(int argc, char **argv)
{

    if (argc != 5)
    {
        printf("Invalid param length, got %d\n", argc);
        return 0;
    }
    const char *romParam = "-ROM";
    const char *fpsParam = "-FPS";
    Window_t *Window = new Window_t();
    Memory_t *Memory = new Memory_t();
    Keyboard_t *Keyboard = new Keyboard_t();
    Display_t *Display = new Display_t(Window);
    CPU_t *CPU = new CPU_t(Memory, Display, Window, Keyboard);

    if (strcmp(argv[1], romParam) == 0 && strcmp(argv[3], fpsParam) == 0)
    {
        int fps = stoi(argv[4], NULL, 10);
        CPU->on(argv[2], fps);
    }
    else
    {
        printf("Invalid: Rom %s FPS %s\n", argv[1], argv[3]);
    }
}
