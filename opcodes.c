/**
    Action816 - A custom 65816 emulator
    (c) 2018, James Maloy and Jeremy Brown, all rights reserved
    Licensed under the MIT license.

    file: opcodes.c
    desc: source file for opcode implementations
    date: 18 April 2018
    updated: 18 April 2018
**/

#include "cpu.h"
#include <stdio.h>

/**
 * ora - opcode 0x1
 * TODO: brief description of what BRK/0 does.
 * @param state current CPU state.
 */
void ora(State65816 *state) {
    printf("debug:(exe op 1 ora) stubbed.\n");
    /*TODO: implement ORA*/
}

/**
 * brk - opcode 0x0
 * TODO: brief description of what BRK/0 does.
 * @param state current CPU state.
 */
void brk(State65816 *state) {
    printf("debug:(exe op 0 brk) we're breaking!\n");
    uint8_t bytes[2]; //create bit differential
    uint16_t orig_Value; //placeholder for original value
    orig_Value = state->pc; //import value
    bytes[0] = *((uint8_t*)&(orig_Value)+1); //high bytes
    bytes[1] = *((uint8_t*)&(orig_Value)+0); //low bytes
    //these two lines beloware crashing the program.
    state->memory[0xFFFE] = bytes[0]; //store the high bytes in memory location FFFE.
    state->memory[0xFFFF] = bytes[1]; //store the low bytes in memory location FFFF.

    /* with the below item, we may need a better method. This is v. sloppy. */
    // this line is crashing the program.
    state->memory[0xFF00] = state->sp;
    //now we retrieve the bytes and put them back together.
    unsigned int retrieve = bytes[0] * 256 + bytes[1];
    //push the value back to the program counter.
    state->pc = retrieve;
}