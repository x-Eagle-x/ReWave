#ifndef __OPCODES__
#define __OPCODES__

#define MEML(op) (OP) (op | 0b10000000)
#define MEMR(op) (OP) (op | 0b01000000)
#define MEMLR(op) (OP) (op | 0b11000000)

enum OP
{
    NOP,
    EXT,
    CALL,
    INT,
    RET,
    JMP,
    JEQ,
    JNQ,
    JHI,
    JLW,
    JHE,
    JLE,

    MOV,
    ADD,
    SUB,
    MUL,
    DIV,

    OR,
    XOR,
    AND,
    NOT,
    SHL,
    SHR,
    CMP,

    LOAD
};

#endif
