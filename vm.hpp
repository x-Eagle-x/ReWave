#ifndef __VM__
#define __VM__

#include "registers.hpp"

#define PROGRAM_SIZE 4096
#define MEMORY_SIZE 1024

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

#if MEMORY_SIZE < 16
    #error "Not enough memory for registers."
#endif

enum
{
    PTR_NONE,
    PTR_LEFT = 1,
    PTR_RIGHT = 2
};

struct VM
{
    bool running = true;

    uint8_t program[PROGRAM_SIZE] = {0}, lr_ptr = 0;
    uint32_t memory[MEMORY_SIZE] = {0}, operands[2] = {0};

    uint32_t &acc_a = memory[REG::A0], &acc_b = memory[REG::B0];
    uint32_t &opcode = memory[REG::C0], &counter = memory[REG::D0];

    void cycle();
    void restart();
};

extern void interrupt(const uint32_t call);

#endif
