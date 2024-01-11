#include "../include/cpu.h"

CPU_t::CPU_t(Memory_t *memory_, Display_t *display_, Window_t *window_, Keyboard_t *keyboard_)
{
    memory = memory_;
    display = display_;
    window = window_;
    keyboard = keyboard_;
}
void CPU_t::cycle()
{
    // Fetch
    uint8_t msb = memory->read(pc);
    uint8_t lsb = memory->read(pc + 1);
    uint16_t instr = (msb << 8) | lsb;
    pc += PC_INC;
    // Decode
    uint8_t opcode = (instr & OP_CODE_MASK) >> OP_SHIFT;
    uint8_t vx = (instr & VX_MASK) >> VX_SHIFT;
    uint8_t vy = (instr & VY_MASK) >> VY_SHIFT;

    uint8_t n = instr & N_MASK;
    uint8_t nn = instr & NN_MASK;
    uint16_t nnn = instr & NNN_MASK;

    printf("Instruction: %04X\n", instr);

    // Exec
    switch (opcode)
    {
    case 0:
        switch (n)
        {
        case 0x00:
            CLS();
            break;
        case 0x0E:
            RET();
            break;
        }

        break;
    case 1:
        JMP(nnn);
        break;
    case 2:
        CALL(nnn);
        break;
    case 3:
        SE(vx, static_cast<uint16_t>(nn));
        break;
    case 4:
        SNE(vx, static_cast<uint16_t>(nn));
        break;
    case 5:
        SE(vx, vy);
        break;
    case 6:
        LD(vx, static_cast<uint16_t>(nn));
        break;
    case 7:
        ADDNN(vx, nn);
        break;
    case 8:
        switch (n)
        {
        case 0:
            LD(vx, vy);
            break;
        case 1:
            OR(vx, vy);
            break;
        case 2:
            AND(vx, vy);
            break;
        case 3:
            XOR(vx, vy);
            break;
        case 4:
            ADD(vx, vy);
            break;
        case 5:
            SUB(vx, vy);
            break;
        case 6:
            SHR(vx, vy);
            break;
        case 7:
            SUBN(vx, vy);
            break;
        case 0x0E:
            SHL(vx, vy);
            break;

        default:
            break;
        }
        break;
    case 9:
        SNE(vx, vy);
        break;
    case 0x0a:
        LD(nnn);
        break;
    case 0x0b:
        JP(nnn);
        break;
    case 0x0c:
        RND(vx, nn);
        break;
    case 0x0d:
        DRW(vx, vy, n);
        break;
    case 0x0e:
        switch (nn)
        {
        case (0x9E):
            SKP(vx);
            break;
        case (0xA1):
            SKNP(vx);
            break;
        }
        break;
    case 0x0f:
        switch (nn)
        {
        case 0x07:
            STDT(vx);
            break;
        case 0x0A:
            LDK(vx);
            break;
        case 0x15:
            LDDT(vx);
            break;
        case 0x18:
            LDST(vx);
            break;
        case 0x1E:
            ADD(vx);
            break;
        case 0x29:
            LDF(vx);
            break;
        case 0x33:
            LDB(vx);
            break;
        case 0x55:
            STI(vx);
            break;
        case 0x65:
            LDI(vx);
            break;
        }
        break;

    default:
        break;
    }
}

void CPU_t::CLS()
{
    display->clear();
}

void CPU_t::JMP(const uint16_t &addr_)
{
    pc = addr_;
}

void CPU_t::LD(const uint8_t &vx_, uint16_t nn_)
{
    v[vx_] = nn_;
}

void CPU_t::ADDNN(const uint8_t &vx_, uint8_t nn_)
{
    v[vx_] += nn_;
}

void CPU_t::LD(const uint16_t &nnn_)
{
    I = nnn_;
}

void CPU_t::LDK(const uint8_t &vx_)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        if (keyboard->getKey(i))
        {
            v[vx_] = i;
            return;
        }
    }

    // Redo if no key pressed, keep going until one is
    pc -= PC_INC;
}

void CPU_t::DRW(const uint8_t &vx_, const uint8_t &vy_, const uint8_t &n_)
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

void CPU_t::SYS(const uint16_t &nnn_)
{
    // Unused, does nothing
}

void CPU_t::RET()
{
    uint16_t addr = stck.top();
    pc = addr;
    stck.pop();
}

void CPU_t::CALL(const uint16_t &addr_)
{
    stck.push(pc);
    pc = addr_;
}

void CPU_t::SE(const uint8_t &vx_, const uint16_t &nn_)
{
    if (v[vx_] == nn_)
    {
        pc += PC_INC;
    }
}

void CPU_t::SNE(const uint8_t &vx_, uint16_t nn_)
{
    if (v[vx_] != nn_)
    {
        pc += PC_INC;
    }
}

void CPU_t::SE(const uint8_t &vx_, const uint8_t &vy_)
{
    if (v[vx_] == v[vy_])
    {
        pc += PC_INC;
    }
}

void CPU_t::LD(const uint8_t &vx_, const uint8_t &vy_)
{
    v[vx_] = v[vy_];
}

void CPU_t::OR(const uint8_t &vx_, const uint8_t &vy_)
{
    v[vx_] |= v[vy_];
    // AND,OR,XOR reset VF
    v[VF] = 0;
}

void CPU_t::AND(const uint8_t &vx_, const uint8_t &vy_)
{
    v[vx_] &= v[vy_];

    // AND,OR,XOR reset VF
    v[VF] = 0;
}

void CPU_t::XOR(const uint8_t &vx_, const uint8_t &vy_)
{
    v[vx_] ^= v[vy_];
    // AND,OR,XOR reset VF
    v[VF] = 0;
}

void CPU_t::ADD(const uint8_t &vx_, const uint8_t &vy_)
{
    uint16_t res = v[vx_] + v[vy_];
    v[vx_] = res & ARITH_8_BIT_RES;
    v[VF] = (res & (1 << ADD_CARRY_BIT)) >> ADD_CARRY_BIT;
}

void CPU_t::SUB(const uint8_t &vx_, const uint8_t &vy_)
{
    uint16_t res16 = v[vx_] - v[vy_];
    uint8_t res8 = v[vx_] - v[vy_];
    v[vx_] = res16 & ARITH_8_BIT_RES;
    v[VF] = res8 == res16;
}

void CPU_t::SHR(const uint8_t &vx_, const uint8_t &vy_)
{

    v[vx_] = v[vy_] >> 1;
    v[VF] = v[vy_] & 1;
}

void CPU_t::SUBN(const uint8_t &vx_, const uint8_t &vy_)
{
    uint16_t res16 = v[vy_] - v[vx_];
    uint8_t res8 = v[vy_] - v[vx_];
    v[vx_] = res16 & ARITH_8_BIT_RES;
    v[VF] = res8 == res16;
}

void CPU_t::SHL(const uint8_t &vx_, const uint8_t &vy_)
{
    v[vx_] = v[vy_] << 1;
    v[VF] = (v[vy_] & (1 << 7)) >> 7;
}

void CPU_t::SNE(const uint8_t &vx_, const uint8_t &vy_)
{
    if (v[vx_] != v[vy_])
    {
        pc += PC_INC;
    }
}

void CPU_t::JP(const uint16_t &addr_)
{
    pc = addr_ + v[0];
}

void CPU_t::RND(const uint8_t &vx_, const uint8_t &nn_)
{
    v[vx_] = nn_ & (rand() % 256);
}

void CPU_t::SKP(const uint8_t &vx_)
{
    if (keyboard->getKey(v[vx_]))
    {
        pc += PC_INC;
    }
}

void CPU_t::SKNP(const uint8_t &vx_)
{
    if (!keyboard->getKey(v[vx_]))
    {
        pc += PC_INC;
    }
}

void CPU_t::LDDT(const uint8_t &vx_)
{
    dt = v[vx_];
}

void CPU_t::STDT(const uint8_t &vx_)
{
    v[vx_] = dt;
}

void CPU_t::LDST(const uint8_t &vx_)
{
    st = v[vx_];
}

void CPU_t::ADD(const uint8_t &vx_)
{
    I += v[vx_];
}

void CPU_t::LDB(const uint8_t &vx_)
{
    uint8_t temp = v[vx_];

    // BCD conversion
    for (uint8_t i = 0; i < 3; i++)
    {
        memory->write(I + 2 - i, temp % 10);
        temp /= 10;
    }
}

void CPU_t::STI(const uint8_t &vx_)
{
    for (uint8_t i = 0; i <= vx_; i++)
    {
        memory->write(I + i, v[i]);
    }
}

void CPU_t::LDI(const uint8_t &vx_)
{
    for (uint8_t i = 0; i <= vx_; i++)
    {
        v[i] = memory->read(I + i);
    }
}

// Load font
void CPU_t::LDF(const uint8_t &vx_)
{
    I = 5 * v[vx_];
}

void CPU_t::on(char *rom_, int fps_)
{
    memory->loadFont();
    char romPrefix[255];
    strcpy(romPrefix, "../rom/");
    strcat(romPrefix, rom_);
    printf("Searching for Rom: %s\n", romPrefix);

    if (!memory->loadROM(romPrefix))
    {
        return;
    }
    printf("Found %s !\n", romPrefix);

    // memory->loadROM("../rom/Pong (alt).ch8");
    window->start();
    bool run = true;
    SDL_Event e;

    high_resolution_clock::time_point cpuT1, cpuT2, sdT1, sdT2;

    cpuT1 = high_resolution_clock::now();
    sdT1 = high_resolution_clock::now();
    duration<double, milli> cpuDT;
    duration<double, milli> sdDT;
    SDL_Scancode scancode;

    while (run)
    {
        // Time differences
        cpuT2 = high_resolution_clock::now();
        sdT2 = high_resolution_clock::now();
        cpuDT = cpuT2 - cpuT1;
        sdDT = sdT2 - sdT1;

        // Cpu cycle
        if (cpuDT.count() >= (1000 * static_cast<double>(1.0 / fps_)))
        {
            cycle();
            cpuT1 = cpuT2;
        }

        // Delay and Sound Register are fixed to 60hz
        if (sdDT.count() >= (1000 * static_cast<double>(1.0 / DELAY_AND_SOUND_HZ)))
        {
            if (dt != 0)
            {
                dt--;
            }
            if (st != 0)
            {
                window->playSound();
                st--;
            }
            else
            {
                window->pauseSound();
            }

            sdT1 = sdT2;
        }

        // Check if still running
        run = window->poll(e);

        // Check keyboard
        switch (e.type)
        {
        case SDL_KEYDOWN:
            scancode = e.key.keysym.scancode;
            if (keyboard->validKey(scancode))
            {
                keyboard->keyDown(keyboard->scanCodeToKey(scancode));
            }
            break;
        case SDL_KEYUP:
            scancode = e.key.keysym.scancode;
            if (keyboard->validKey(scancode))
            {
                keyboard->keyUp(keyboard->scanCodeToKey(scancode));
            }
            break;
        }
    }

    window->destroy();
}