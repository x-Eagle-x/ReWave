#ifndef __OPCODES__
#define __OPCODES__

#define MEM 0x80
#define MEM_OPCODE(o) (o + MEM)

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
    CMP
};

#endif