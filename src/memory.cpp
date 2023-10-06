#include "../include/memory.h"

Memory_t::Memory_t(){

};

uint8_t Memory_t::read(uint16_t addr_)
{
    return memory[addr_];
}

Memory_t::~Memory_t() {}

void Memory_t::loadFont()
{
    for (uint8_t i = 0; i < 80; i++)
    {
        memory[i] = font[i];
    }
}

void Memory_t::loadROM(char *path_)
{
    FILE *rom = fopen(path_, "rb");
    int j = 0;

    // Read each byte
    int byte;
    while (byte != EOF)
    {
        byte = fgetc(rom);
        memory[0x200 + j] = byte;
        j++;
    }
    fclose(rom);

    for (int i = 0x200; i < 0x200 + j - 1; i++)
    {
        printf("Mem %d, 0x%x\n", i, memory[i]);
    }
}