#include "../include/memory.h"

Memory_t::Memory_t(){

};

uint8_t Memory_t::read(const uint16_t &addr_)
{
    return memory[addr_];
}

void Memory_t::write(const uint16_t &addr_, const uint8_t &data_)
{
    memory[addr_] = data_;
}

Memory_t::~Memory_t() {}

void Memory_t::loadFont()
{
    for (uint8_t i = 0; i < FONT_SIZE; i++)
    {
        write(i, font[i]);
    }
}

bool Memory_t::loadROM(const char *path_)
{
    FILE *rom = fopen(path_, "rb");

    if (!rom)
    {
        printf("Rom not found\n");
        return false;
    }
    int j = 0;

    // Read each byte
    int byte;
    while (byte != EOF)
    {
        byte = fgetc(rom);
        write(ROM_START + j, byte);
        j++;
    }
    fclose(rom);

    for (int i = ROM_START; i < ROM_START + j - 1; i++)
    {
        printf("Mem %d, 0x%x\n", i, read(i));
    }
    return true;
}