/**
    Action816 - A custom 65816 emulator
    (c) 2018, James Maloy and Jeremy Brown, all rights reserved
    Licensed under the MIT license.

    file: main.c
    desc: "Base for which we invent the universe."
    date: 13 April 2018
    updated: 17 April 2018
**/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct State65816 {
    uint16_t pc; //Program Counter
    uint8_t sp; //Stack Pointer
    uint8_t acc; //Accumulator
    uint8_t irx; //Index Register X
    uint8_t iry; //Index Register Y
    uint8_t sysFlags; //system flags:
    /*  bit 0: carry
        bit 1: zero
        bit 2: IRQ disable
        bit 3: decimal mode
        bit 4: break instruction
        bit 5: unimplemented (do not use)
        bit 6: overflow
        bit 7: negative */
    uint16_t *memory; //Memory allocation
} State65816;

/**
 * reset6502 - resets the processor to the power on state for 6502 Emulation mode
 * @param instance instance of the emulated CPU to reset.
 */
void reset6502(State65816 *instance) {
    /*instance->pc = 0xFFFC;
    instance->sysFlags = 0b00000100; //binary set, disable decimal mode, enable IRQ disable
    instance->sp = 0x00FF; //temporary, will remove later.
    instance->sysFlags = 0b00001000; //binary set, enable decimal mode*/

    /* this is done based on suggestion from https://goo.gl/kgvkRk;
    demonstrating the process in which a 6502 processor initializes. */
}

/**
 * Init6502 - initial "initialization" of the processor function for 6502 Emulation mode.
 * @param void
 * @return a valid CPU state object.
 */
State65816* Init6502(void) {
    size_t mem_size = 0x10000;
    State65816* state = calloc(1, sizeof(State65816));
    state->memory = malloc(mem_size); //this should have 64 kilobytes allocated
    printf("%d bytes allocated.\n", _msize(state->memory)); //and it does
    reset6502(state); //invoke a reset
    return state;
}

/**
 * brk - opcode 0
 * TODO: brief description of what BRK/0 does.
 * noste: this function is written against the prototype for a function pointer, make sure the signatures match!
 * @param state current CPU state.
 */
void brk(State65816 *state) {
    printf("debug:(exe op 0 brk) we're breaking!\n");
    uint8_t bytes[2]; //create bit differential
    uint16_t orig_Value; //placeholder for original value
    orig_Value = state->pc; //import value
    bytes[0] = *((uint8_t*)&(orig_Value)+1); //high bytes
    bytes[1] = *((uint8_t*)&(orig_Value)+0); //low bytes

    //state->memory[0xFFFE] = bytes[0]; //store the high bytes in memory location FFFE.
    //state->memory[0xFFFF] = bytes[1]; //store the low bytes in memory location FFFF.

    /* with the below item, we may need a better method. This is v. sloppy. */
    //state->memory[0xFF00] = state->sp;



    //now we retrieve the bytes and put them back together.
    unsigned int retrieve = bytes[0] * 256 + bytes[1];
    //push the value back to the program counter.
    state->pc = retrieve;
}

void ora(State65816 *state) {
    printf("debug:(exe op 1 ora) stubbed.\n");
}

void opcodeCheck(char opcode, State65816 *state) {
    void (*opCodeExec)(State65816 *mystate) = NULL;   // function pointer for which opcode function to call next.
    switch(opcode) {
        case 0x0: //BRK b -- 6502 opcode
            opCodeExec = &brk;
            break;
        case 0x1: //ORA (d, X) -- 6502 opcode
            opCodeExec = &ora;
            break;
        case 0x2: //cop b -- 65816 exclusive opcode
            break;
    }
    if(opCodeExec != NULL) (*opCodeExec)(state);
    else printf("illegal/unimplemented opcode: %i\n", opcode);
}

int main(int argc, char** argv) {
    State65816* state = Init6502();
    //unsigned long long int cycles = 0;
    for(state->pc = 0; state->pc < 10; state->pc++) {
        printf("pc=%u\n", state->pc);
        //CRASH AT 36827
        char cOpCode = state->memory[state->pc];
        printf("op=%i\n", (int) cOpCode);
        opcodeCheck(cOpCode, state);
        //cycles++; // maybe the function pointer should return the amount of cycles executed?
    }
    return 0;
}
