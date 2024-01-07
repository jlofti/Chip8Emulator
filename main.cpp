#include <iostream>
#include "include/memory.h"
#include "include/cpu.h"
#include "include/display.h"
#include "include/window.h"

int main(int, char **)
{
    Window_t *Window = new Window_t();
    Memory_t *Memory = new Memory_t();
    Display_t *Display = new Display_t(Window);
    CPU_t *CPU = new CPU_t(Memory, Display, Window);
    CPU->on();
}
