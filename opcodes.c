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
 * brk - opcode 0x00
 * @desc: This opcode is supposed to initiate a break from currently executing code.
 * @param: state current CPU state.
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
 * ora - opcode 0x01
 * TODO: brief description of what ORA/1 does.
 * @param state current CPU state.
 */
void ora(State65816 *state) {
    printf("debug:(exe op 1 ora) stubbed.\n\n");
    /*TODO: implement ORA*/
}

/**
 * nop - opcode 0xEA
 * @desc: This literally does nothing.
 * @param: nothing.
 */

void nop(State65816 *state) {
  printf("debug:(exe op ea nop) executed.\n\n");
}

/**
 * tax - opcode 0xAA
 * @desc: Copy accumulator value into INX.
 *
 * txa - opcode 0x8A
 * @desc: Copy INX into accumulator.
 *
 */
void tax(State65816 *state) {
  state->irx = state->acc;
  printf("debug: (exe op aa tax) executed.\n\n");
}

void txa(State65816 *state) {
  state->acc = state->irx;
  printf("debug: (exe op 8a txa) executed.\n\n");
}

/**
 * tay - opcode 0xA8
 * @desc: Copy accumulator value to INY.
 *
 * tya - opcode 0x98
 * @desc: Copy INY into accumulator.
 *
 */

void tay(State65816 *state) {
  state->iry = state->acc;
  printf("debug: (exe op aa tax) executed.\n\n");
}

void tya(State65816 *state) {
  state->acc = state->iry;
  printf("debug: (exe op 8a txa) executed.\n\n");
}

/**
 * dex - opcode 0xCA
 * @desc: Decease Index Register X by one.
 *
 * inx - opcode 0xE8
 * @desc: Increase Index Register X by one.
 *
 * dey - opcode 0x88
 * @desc: Decrease INY by one.
 *
 * iny - opcode 0xC8
 * @desc: Increase INY by one.
 */
void dex(State65816 *state) {
  state->irx = (state->irx)-1;
}

void inx(State65816 *state) {
  state->irx = (state->irx)+1;
}

void dey(State65816 *state){
  state->iry = (state->iry)-1;
}

void iny(State65816 *state) {
  state->iry = (state->iry)+1;
}



