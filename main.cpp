#include <iostream>
#include "include/memory.h"
#include "include/cpu.h"
#include "include/display.h"

int main(int, char **)
{
    Memory_t *Memory = new Memory_t();
    Display_t *Display = new Display_t();
    CPU_t *CPU = new CPU_t(Memory, Display);
    CPU->on();
}
