/**
    Action816 - A custom 65816 emulator
    (c) 2018, James Maloy and Jeremy Brown, all rights reserved
    Licensed under the MIT license.

    file: cpu.h
    desc: opcode function prototypes
    date: 18 April 2018
    updated: 18 April 2018
**/

#ifndef OPCODES_H_INCLUDED
#define OPCODES_H_INCLUDED

/* prototype table */
void ora(State65816 *state);
void brk(State65816 *state);
void nop(State65816 *state);
void tax(State65816 *state);
void tay(State65816 *state);
void tya(State65816 *state);
void txa(State65816 *state);
void dex(State65816 *state);
void inx(State65816 *state);
void dey(State65816 *state);
void iny(State65816 *state);

#endif // OPCODES_H_INCLUDED
