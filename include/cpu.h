#pragma once
#include <stdint.h>
#include <stack>
#include "memory.h"
#include "display.h"
#include <pthread.h>
#include <SDL2/SDL.h>

#include <unistd.h> // for linux

using namespace std;

#define OP_CODE_MASK 0xF000
#define VX_MASK 0x0F00
#define VY_MASK 0x00F0
#define N_MASK 0x000F
#define NN_MASK 0x00FF
#define NNN_MASK 0x0FFF

#define OP_SHIFT 12
#define VX_SHIFT 8
#define VY_SHIFT 4

class CPU_t
{

private:
    // Regs
    uint8_t v[16];
    uint16_t I = 0;
    stack<uint16_t> stack;
    uint8_t dt;
    uint8_t st;
    uint16_t pc = 0x200;
    Memory_t *memory;
    Display_t *display;

public:
    CPU_t(Memory_t *mem_, Display_t *disp_);
    ~CPU_t();

    // void SYS(uint16_t nnn_);
    void CLS();
    // void RET();
    void JMP(uint16_t nnn_);
    /* void CALL(uint16_t addr_);
     void SE(uint8_t vx_, uint16_t val_);
     void SNE(uint8_t vx_, uint16_t instr_);
     void SE(uint8_t vx_, uint8_t vy);*/
    void LD(uint8_t vx_, uint16_t nn_);
    void ADDNN(uint8_t vx_, uint8_t nn_);
    /*void LD(uint8_t vx_, uint8_t vy_);
    void OR(uint8_t vx_, uint8_t vy_);
    void AND(uint8_t vx_, uint8_t vy);
    void XOR(uint8_t vx_, uint8_t vy);
    void ADD(uint8_t vx_, uint8_t vy_);
    void SUB(uint8_t vx_, uint8_t vy_);
    void SHR(uint8_t vx_);
    void SUBN(uint8_t vx_, uint8_t vy_);
    void SHL(uint8_t vx_);
    void SNE(uint8_t vx_, uint8_t vy_);*/
    void LD(uint16_t nnn_);
    // void JP(uint16_t addr_);
    // void RND(uint8_t vx_, uint8_t data_);
    void DRW(uint8_t vx_, uint8_t vy_, uint8_t n_);
    /* void SKP(uint8_t vx_);
     void SKNP(uint8_t vx_);
     void LDDT(uint8_t vx_);
     void LDST(uint8_t vx_);
     void ADD(uint8_t data_);
     void LDF(uint8_t vx_);
     void LDB(uint8_t vx_);
     void STI(uint8_t vx_);
     void LDI(uint8_t vx_);*/

    void cycle();
    void on();
};