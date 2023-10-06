#include "../include/cpu.h"

CPU_t::CPU_t(Memory_t *mem_, Display_t *disp_)
{
    memory = mem_;
    display = disp_;
}
void CPU_t::cycle()
{
    // Fetch
    uint8_t msb = memory->read(pc);
    uint8_t lsb = memory->read(pc + 1);
    uint16_t instr = (msb << 8) | lsb;
    pc += 0x02;
    // Decode
    uint8_t opcode = (instr & OP_CODE_MASK) >> OP_SHIFT;
    uint8_t vx = (instr & VX_MASK) >> VX_SHIFT;
    uint8_t vy = (instr & VY_MASK) >> VY_SHIFT;

    uint8_t n = instr & N_MASK;
    uint8_t nn = instr & NN_MASK;
    uint16_t nnn = instr & NNN_MASK;

    printf("Instruction: %04X", instr);
    // printf("OPCODE: 0x%01X VX: 0x%01X, VY: 0x%01X, N: 0x%01X, NN: 0x%02X, NNN: 0x%03X\n", opcode, vx, vy, n, nn, nnn);

    // Exec
    switch (opcode)
    {
    case 0:
        printf("Clear sceen\n");
        CLS();
        break;
    case 1:
        printf("Jump\n");
        JMP(nnn);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        printf("LD\n");
        LD(vx, nn);
        break;
    case 7:
        printf("ADDNN\n");
        ADDNN(vx, nn);
        break;
    case 8:
        break;
    case 9:
        break;
    case 0x0a:
        printf("LDNNN\n");
        LD(nnn);
        break;
    case 0x0b:
        break;
    case 0x0c:
        break;
    case 0x0d:
        printf("DRW\n");
        DRW(vx, vy, n);
        break;
    case 0x0e:
        break;
    case 0x0f:
        break;

    default:
        break;
    }

    sleep(1);
}

void CPU_t::CLS()
{
    display->clear();
}

void CPU_t::JMP(uint16_t nnn_)
{
    pc = nnn_;
}

void CPU_t::LD(uint8_t vx_, uint16_t nn_)
{
    v[vx_] = nn_;
}

void CPU_t::ADDNN(uint8_t vx_, uint8_t nn_)
{
    v[vx_] += nn_;
}

void CPU_t::LD(uint16_t nnn_)
{
    I = nnn_;
}

void CPU_t::DRW(uint8_t vx_, uint8_t vy_, uint8_t n_)
{
    uint8_t x = v[vx_] % WIDTH;
    uint8_t y = v[vy_] % HEIGHT;
    v[0xF] = 0;

    for (uint8_t i = 0; i < n_; i++)
    {
        uint8_t spriteByte = memory->read(I + i);

        for (int j = 0; j < 8; j++)
        {
            uint8_t spriteBit = spriteByte & (0x80u >> j);
            uint8_t pixelOn = display->check(x + j, y + i);

            // Sprite Bit is on and Pixel is On
            if (spriteBit && pixelOn)
            {
                v[0xf] = 1;
                display->clearPixel(x + j, y + i);
            }

            // Sprite Bit is on and Pixel is Off
            else if (spriteBit && !pixelOn)
            {
                v[0xf] = 0;
                display->drawPixel(x + j, y + i);
            }
        }
    }
    display->update();
};

void CPU_t::on()
{
    pthread_t displayThread;
    memory->loadFont();
    memory->loadROM("../rom/ibm.ch8");
    display->start([&]
                   { return this->cycle(); });
    // pthread_create(&displayThread, NULL, display->start, NULL);
}