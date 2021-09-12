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
            auto oldpoint = counter, newpoint = operands[LEFT];
            counter = newpoint;

            while (running)
            {
                cycle();
            }

            counter = oldpoint;
            running = true;

            break;
        }

        case OP::INT: PREPARE_OPERAND(LEFT);
        {
            interrupt(OPERAND(LEFT));
            break;
        }

        case OP::RET:
        {
            running = false;
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

        case OP::MOV: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] = OPERAND(RIGHT);
            break;
        }

        case OP::ADD: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] += OPERAND(RIGHT);
            break;
        }

        case OP::SUB: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] -= OPERAND(RIGHT);
            break;
        }

        case OP::DIV: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] /= OPERAND(RIGHT);
            break;
        }

        case OP::MUL: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] *= OPERAND(RIGHT);
            break;
        }

        case OP::OR: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] |= OPERAND(RIGHT);
            break;
        }

        case OP::XOR: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] ^= OPERAND(RIGHT);
            break;
        }

        case OP::AND: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] &= OPERAND(RIGHT);
            break;
        }

        case OP::SHL: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] >>= OPERAND(RIGHT);
            break;
        }

        case OP::SHR: PREPARE_OPERANDS();
        {
            memory[operands[LEFT]] <<= OPERAND(RIGHT);
            break;
        }

        case OP::CMP: PREPARE_OPERANDS();
        {
            acc_a = memory[operands[LEFT]];
            acc_b = OPERAND(RIGHT);
            break;
        }

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