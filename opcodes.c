/**
    Action816 - A custom 65816 emulator
    (c) 2018, James Maloy and Jeremy Brown, all rights reserved
    Licensed under the MIT license.

    file: opcodes.c
    desc: source file for opcode implementations
    date: 18 April 2018
    updated: 18 April 2018
**/

#include <stdio.h>
#include "cpu.h"
#include "opcodes.h"

/**
 * brk - opcode 0x0
 * TODO: brief description of what BRK/0 does.
 * @param state current CPU state.
 */
void brk(State65816 *state) {

    uint8_t bytes[2]; //create bit differential
    uint16_t orig_Value; //placeholder for original value

    orig_Value = state->pc; //import value

    bytes[0] = *((uint8_t*)&(orig_Value)+1); //high bytes
    bytes[1] = *((uint8_t*)&(orig_Value)+0); //low bytes
    state->memory[0xFFFE] = bytes[0]; //store the high bytes in memory location FFFE.
    state->memory[0xFFFF] = bytes[1]; //store the low bytes in memory location FFFF.
    state->memory[0xFF00] = state->sp; //push contents of memory location FF00 to the stack pointer.
    printf("original value: %d\n", orig_Value);
    printf("high bytes FFFE: %x\n", state->memory[0xFFFE]);
    printf("low bytes FFFF: %x\n", state->memory[0xFFFF]);
    printf("stack pointer storage at FF00: %d\n", state->memory[0xFF00]);
    //now we retrieve the bytes and put them back together.
    unsigned int retrieve = bytes[0] * 256 + bytes[1];
    //push the value back to the program counter.
    state->pc = retrieve;
    printf("program counter: %d\n", state->pc);
    printf("debug:(exe op 0 brk) executed.\n\n");
}

/**
 * ora - opcode 0x1
 * TODO: brief description of what ORA/1 does.
 * @param state current CPU state.
 */
void ora(State65816 *state) {
    printf("debug:(exe op 1 ora) stubbed.\n\n");
    /*TODO: implement ORA*/
}
