#pragma once
#include <stdint.h>
#include <stack>
#include "memory.h"
#include "display.h"
#include "window.h"
#include "keyboard.h"

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

#include <chrono>

#include <unistd.h> // for linux

using namespace std;
using namespace std::chrono;

#define OP_CODE_MASK 0xF000
#define VX_MASK 0x0F00
#define VY_MASK 0x00F0
#define N_MASK 0x000F
#define NN_MASK 0x00FF
#define NNN_MASK 0x0FFF
#define ADD_CARRY_BIT 8
#define ARITH_8_BIT_RES 0xFF

#define OP_SHIFT 12
#define VX_SHIFT 8
#define VY_SHIFT 4

#define PC_INC 0x02

#define REG_SIZE 16
#define VF 15

#define FPS 5
#define DELAY_AND_SOUND_HZ 60

class CPU_t
{

private:
    // Regs
    uint8_t v[REG_SIZE] = {0};
    uint16_t I = 0;
    stack<uint16_t> stck;
    uint8_t dt = 0;
    uint8_t st = 0;
    uint16_t pc = ROM_START;
    Memory_t *memory;
    Display_t *display;
    Window_t *window;
    Keyboard_t *keyboard;

public:
    CPU_t(Memory_t *mem_, Display_t *disp_, Window_t *window, Keyboard_t *keyboard_);
    ~CPU_t();

    void SYS(uint16_t nnn_);
    void CLS();
    void RET();
    void JMP(uint16_t nnn_);
    void CALL(uint16_t addr_);
    void SE(uint8_t vx_, uint16_t val_);
    void SNE(uint8_t vx_, uint16_t val_);
    void SE(uint8_t vx_, uint8_t vy);
    void LD(uint8_t vx_, uint16_t nn_);
    void ADDNN(uint8_t vx_, uint8_t nn_);
    void LD(uint8_t vx_, uint8_t vy_);
    void OR(uint8_t vx_, uint8_t vy_);
    void AND(uint8_t vx_, uint8_t vy_);
    void XOR(uint8_t vx_, uint8_t vy_);
    void ADD(uint8_t vx_, uint8_t vy_);
    void SUB(uint8_t vx_, uint8_t vy_);
    void SHR(uint8_t vx_, uint8_t vy_);
    void SUBN(uint8_t vx_, uint8_t vy_);
    void SHL(uint8_t vx_, uint8_t vy_);
    void SNE(uint8_t vx_, uint8_t vy_);
    void LD(uint16_t nnn_);
    void JP(uint16_t addr_);
    void RND(uint8_t vx_, uint8_t nn_);
    void DRW(uint8_t vx_, uint8_t vy_, uint8_t n_);
    void SKP(uint8_t vx_);
    void SKNP(uint8_t vx_);
    void LDDT(uint8_t vx_);
    void LDK(uint8_t vx_);
    void LDST(uint8_t vx_);
    void STDT(uint8_t vx_);
    void ADD(uint8_t vx_);
    void LDF(uint8_t vx_);
    void LDB(uint8_t vx_);
    void STI(uint8_t vx_);
    void LDI(uint8_t vx_);

    void cycle();
    void on();
};