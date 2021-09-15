#include "vm.hpp"
#include "opcodes.hpp"

void get_operand(uint32_t &buffer, uint32_t &counter, const uint8_t program[])
{
    buffer |= program[++counter]; buffer <<= 8;
    buffer |= program[++counter]; buffer <<= 8;
    buffer |= program[++counter]; buffer <<= 8;
    buffer |= program[++counter];
}

enum
{
    LEFT,
    RIGHT
};

#define PREPARE_OPERAND(x) get_operand(operands[x], counter, program)
#define PREPARE_OPERANDS() PREPARE_OPERAND(LEFT); PREPARE_OPERAND(RIGHT)
#define OPERAND(x) (use_memory ? memory[operands[x]] : operands[x])

#define RESET_ACCUMULATORS() acc_a = acc_b = 0
#define CONTROL_FLOW(x) PREPARE_OPERAND(LEFT); if (acc_a x acc_b) {counter = OPERAND(LEFT); RESET_ACCUMULATORS(); return;} break
#define OPERATOR(x) PREPARE_OPERANDS(); memory[operands[LEFT]] x OPERAND(RIGHT); break;

void VM::cycle()
{
    opcode = program[counter];
    use_memory = operands[0] = operands[1] = 0;

    if (opcode >= MEM)
    {
        opcode -= MEM;
        use_memory = true;
    }

    switch (opcode)
    {
        case OP::NOP:
        {
            break;
        }

        case OP::CALL: PREPARE_OPERAND(LEFT);
        {
            auto oldpoint = counter, newpoint = operands[LEFT]; counter = newpoint;

            while (running)
            {
                cycle();
            }

            running = counter = oldpoint;
            break;
        }

        case OP::INT: PREPARE_OPERAND(LEFT);
        {
            interrupt(OPERAND(LEFT));
            break;
        }

        case OP::JMP: PREPARE_OPERAND(LEFT);
        {
            counter = OPERAND(LEFT);
            return;
        }

        case OP::JEQ: CONTROL_FLOW(==);
        case OP::JNQ: CONTROL_FLOW(!=);
        case OP::JHI: CONTROL_FLOW(>);
        case OP::JLW: CONTROL_FLOW(<);
        case OP::JHE: CONTROL_FLOW(>=);
        case OP::JLE: CONTROL_FLOW(<=);

        case OP::MOV: OPERATOR(=);
        case OP::ADD: OPERATOR(+=);
        case OP::SUB: OPERATOR(-=);
        case OP::DIV: OPERATOR(/-);
        case OP::MUL: OPERATOR(*=);

        case OP::OR:  OPERATOR(|=);
        case OP::XOR: OPERATOR(^=);
        case OP::AND: OPERATOR(&=);
        case OP::SHL: OPERATOR(<<=);
        case OP::SHR: OPERATOR(>>=);

        case OP::CMP: PREPARE_OPERANDS();
        {
            acc_a = memory[operands[LEFT]];
            acc_b = OPERAND(RIGHT);
            break;
        }

        case OP::RET:
        case OP::EXT:
        default:
        {
            running = false;
            break;
        }
    }

    counter++;
}

void VM::restart()
{
    counter = 0;
    running = true;
}
