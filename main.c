/**
    Action816 - A custom 65816 emulator
    (c) 2018, James Maloy and Jeremy Brown, all rights reserved
    Licensed under the MIT license.

    file: main.c
    desc: "Base for which we invent the universe."
    date: 13 April 2018
    updated: 18 April 2018
**/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "opcodes.h"

/**
 * reset6502 - resets the processor to the power on state for 6502 Emulation mode
 * @param instance instance of the emulated CPU to reset.
 */
void reset6502(State65816 *instance) {
    instance->pc = 0xFFFC;
    instance->sysFlags = 0b00000100; //binary set, disable decimal mode, enable IRQ disable
    instance->sp = 0x00FF; //temporary, will remove later.
    instance->sysFlags = 0b00001000; //binary set, enable decimal mode

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
 * opcodeCheck
 * calls the appropriate function for a given opcode.
 * @param opcode - opcode in the emulated machine's memory
 * @param state - pointer to an emulated CPU.
 */
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
    for(state->pc = 0; state->pc < 10; state->pc++) { /*for(;;) {*/
        printf("pc=%u\n", state->pc);
        //crash at 36827 seemingly.
        char cOpCode = state->memory[state->pc];
        printf("op=%i\n", (int) cOpCode);
        opcodeCheck(cOpCode, state);
        //cycles++; // maybe the function pointer should return the amount of cycles executed?
    }
    return 0;
}
