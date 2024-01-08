#include "../include/cpu.h"

CPU_t::CPU_t(Memory_t *mem_, Display_t *disp_, Window_t *window_, Keyboard_t *keyboard_)
{
    memory = mem_;
    display = disp_;
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
    //  printf("OPCODE: 0x%01X VX: 0x%01X, VY: 0x%01X, N: 0x%01X, NN: 0x%02X, NNN: 0x%03X\n", opcode, vx, vy, n, nn, nnn);

    // Exec
    switch (opcode)
    {
    case 0:

        switch (n)
        {
        case 0x00:
            // printf("Clear sceen\n");
            CLS();
            break;
        case 0x0E:
            // printf("Ret\n");
            RET();
            break;
        }

        break;
    case 1:
        // printf("Jump\n");
        JMP(nnn);
        break;
    case 2:
        // printf("Call\n");
        CALL(nnn);
        break;
    case 3:
        // printf("Skip Next Instr\n");
        SE(vx, static_cast<uint16_t>(nn));
        break;
    case 4:
        // printf("!Skip Next Instr\n");
        SNE(vx, static_cast<uint16_t>(nn));
        break;
    case 5:
        // printf("Skip Next Instr\n");
        SE(vx, vy);
        break;
    case 6:
        // printf("LD\n");
        LD(vx, static_cast<uint16_t>(nn));
        break;
    case 7:
        // printf("ADDNN\n");
        ADDNN(vx, nn);
        break;
    case 8:
        switch (n)
        {
        case 0:
            // printf("LD");
            LD(vx, vy);
            break;
        case 1:
            // printf("OR\n");
            OR(vx, vy);
            break;
        case 2:
            // printf("AND\n");
            AND(vx, vy);
            break;
        case 3:
            // printf("XOR\n");
            XOR(vx, vy);
            break;
        case 4:
            // printf("ADD\n");
            ADD(vx, vy);
            break;
        case 5:
            // printf("SUB\n");
            SUB(vx, vy);
            break;
        case 6:
            // printf("SHR\n");
            SHR(vx, vy);
            break;
        case 7:
            // printf("SUBN\n");
            SUBN(vx, vy);
            break;
        case 0x0E:
            // printf("SHL\n");
            SHL(vx, vy);
            break;

        default:
            break;
        }
        break;
    case 9:
        //  printf("!Skip Next Instr\n");
        SNE(vx, vy);
        break;
    case 0x0a:
        // printf("LDNNN\n");
        LD(nnn);
        break;
    case 0x0b:
        JP(nnn);
        break;
    case 0x0c:
        RND(vx, nn);
        break;
    case 0x0d:
        // printf("DRW\n");
        DRW(vx, vy, n);
        break;
    case 0x0e:
        switch (nn)
        {
        case (0x9E):
            //  printf("Skip Key\n");
            SKP(vx);
            break;
        case (0xA1):
            // printf("!Skip Key\n");
            SKNP(vx);
            break;
        }
        break;
    case 0x0f:
        switch (nn)
        {
        case 0x07:
            // printf("Ld DT\n");
            LDDT(vx);
            break;
        case 0x0A:
            // printf("LD k\n");
            LDK(vx);
            break;
        case 0x15:
            // printf("LDDT\n");
            LDDT(vx);
            break;
        case 0x18:
            // printf("LDST\n");
            LDST(vx);
            break;
        case 0x1E:
            // printf("ADD\n");
            ADD(vx);
            break;
        case 0x29:
            //  printf("LDF\n");
            LDF(vx);
            break;
        case 0x33:
            // printf("LDB\n");
            LDB(vx);
            break;
        case 0x55:
            // printf("STI\n");
            STI(vx);
            break;
        case 0x65:
            // printf("LDI\n");
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

void CPU_t::JMP(uint16_t nnn_)
{
    pc = nnn_;
}

void CPU_t::LD(uint8_t vx_, uint16_t nn_)
{
    v[vx_] = nn_;
}

void CPU_t::STDT(uint8_t vx_)
{
    dt = v[vx_];
}

void CPU_t::ADDNN(uint8_t vx_, uint8_t nn_)
{
    v[vx_] += nn_;
}

void CPU_t::LD(uint16_t nnn_)
{
    I = nnn_;
}

void CPU_t::LDK(uint8_t vx_)
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

void CPU_t::SYS(uint16_t nnn_)
{
    // Unused, does nothing
}

void CPU_t::RET()
{
    uint16_t addr = stck.top();
    pc = addr;
    stck.pop();
}

void CPU_t::CALL(uint16_t addr_)
{
    stck.push(pc);
    pc = addr_;
}

void CPU_t::SE(uint8_t vx_, uint16_t val_)
{
    if (v[vx_] == val_)
    {
        pc += PC_INC;
    }
}

void CPU_t::SNE(uint8_t vx_, uint16_t val_)
{
    if (v[vx_] != val_)
    {
        pc += PC_INC;
    }
}

void CPU_t::SE(uint8_t vx_, uint8_t vy_)
{
    if (v[vx_] == v[vy_])
    {
        pc += PC_INC;
    }
}

void CPU_t::LD(uint8_t vx_, uint8_t vy_)
{
    v[vx_] = v[vy_];
}

void CPU_t::OR(uint8_t vx_, uint8_t vy_)
{
    v[vx_] |= v[vy_];
    // AND,OR,XOR reset VF
    v[VF] = 0;
}

void CPU_t::AND(uint8_t vx_, uint8_t vy_)
{
    v[vx_] &= v[vy_];

    // AND,OR,XOR reset VF
    v[VF] = 0;
}

void CPU_t::XOR(uint8_t vx_, uint8_t vy_)
{
    v[vx_] ^= v[vy_];
    // AND,OR,XOR reset VF
    v[VF] = 0;
}

void CPU_t::ADD(uint8_t vx_, uint8_t vy_)
{
    uint16_t res = v[vx_] + v[vy_];
    v[vx_] = res & ARITH_8_BIT_RES;
    v[VF] = (res & (1 << ADD_CARRY_BIT)) >> ADD_CARRY_BIT;
}

void CPU_t::SUB(uint8_t vx_, uint8_t vy_)
{
    uint16_t res16 = v[vx_] - v[vy_];
    uint8_t res8 = v[vx_] - v[vy_];
    v[vx_] = res16 & ARITH_8_BIT_RES;
    v[VF] = res8 == res16;
}

void CPU_t::SHR(uint8_t vx_, uint8_t vy_)
{

    v[vx_] = v[vy_] >> 1;
    v[VF] = v[vy_] & 1;
}

void CPU_t::SUBN(uint8_t vx_, uint8_t vy_)
{
    uint16_t res16 = v[vy_] - v[vx_];
    uint8_t res8 = v[vy_] - v[vx_];
    v[vx_] = res16 & ARITH_8_BIT_RES;
    v[VF] = res8 == res16;
}

void CPU_t::SHL(uint8_t vx_, uint8_t vy_)
{
    v[vx_] = v[vy_] << 1;
    v[VF] = (v[vy_] & (1 << 7)) >> 7;
}

void CPU_t::SNE(uint8_t vx_, uint8_t vy_)
{
    if (v[vx_] != v[vy_])
    {
        pc += PC_INC;
    }
}

void CPU_t::JP(uint16_t addr_)
{
    pc = addr_ + v[0];
}

void CPU_t::RND(uint8_t vx_, uint8_t nn_)
{
    v[vx_] = nn_ & (rand() % 256);
}

// Keyboard
void CPU_t::SKP(uint8_t vx_)
{
    if (keyboard->getKey(v[vx_]))
    {
        pc += PC_INC;
    }
}

// Keyboard
void CPU_t::SKNP(uint8_t vx_)
{
    if (!keyboard->getKey(v[vx_]))
    {
        pc += PC_INC;
    }
}

// Delay Timer
void CPU_t::LDDT(uint8_t vx_)
{
    dt = v[vx_];
}

void CPU_t::LDST(uint8_t vx_)
{
    st = v[vx_];
}

void CPU_t::ADD(uint8_t vx_)
{
    I += v[vx_];
}

void CPU_t::LDB(uint8_t vx_)
{
    uint8_t temp = v[vx_];

    for (uint8_t i = 0; i < 3; i++)
    {
        memory->write(I + 2 - i, temp % 10);
        temp /= 10;
    }
}

void CPU_t::STI(uint8_t vx_)
{
    for (uint8_t i = 0; i <= vx_; i++)
    {
        memory->write(I + i, v[i]);
    }
}

void CPU_t::LDI(uint8_t vx_)
{
    for (uint8_t i = 0; i <= vx_; i++)
    {
        v[i] = memory->read(I + i);
    }
}

// Load font
void CPU_t::LDF(uint8_t vx_)
{
}

void CPU_t::on()
{
    memory->loadFont();
    memory->loadROM("../rom/5-quirks.ch8");
    window->start();
    bool run = true;
    SDL_Event e;

    high_resolution_clock::time_point cpuT1, cpuT2, sdT1, sdT2;

    cpuT1 = high_resolution_clock::now();
    sdT1 = high_resolution_clock::now();
    duration<double, milli> cpuDT;
    duration<double, milli> sdDT;

    while (run)
    {
        // Time differences
        cpuT2 = high_resolution_clock::now();
        sdT2 = high_resolution_clock::now();
        cpuDT = cpuT2 - cpuT1;
        sdDT = sdT2 - sdT1;

        // Cpu cycle
        if (cpuDT.count() >= ((1000 * static_cast<double>(1 / FPS))))
        {
            cycle();
            cpuT1 = cpuT2;
        }

        // Delay and Sound Register are fixed to 60hz
        if (sdDT.count() >= (1000 * static_cast<double>(1 / DELAY_AND_SOUND_HZ)))
        {
            if (dt != 0)
            {
                dt--;
            }
            if (st != 0)
            {
                st--;
            }

            sdT1 = sdT2;
        }

        // Check if still running
        run = window->poll(e);

        // Check keyboard
        switch (e.type)
        {
        case SDL_KEYDOWN:
            keyboard->keyDown(keyboard->scanCodeToKey(e.key.keysym.scancode));
            break;
        case SDL_KEYUP:
            keyboard->keyUp(keyboard->scanCodeToKey(e.key.keysym.scancode));
            break;
        }
    }

    window->destroy();
}