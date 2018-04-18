/**
    Action816 - A custom 65816 emulator
    (c) 2018, James Maloy and Jeremy Brown, all rights reserved
    Licensed under the MIT license.

    file: cpu.h
    desc: source file for the CPU structure.
    date: 18 April 2018
    updated: 18 April 2018
**/

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
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

#endif // CPU_H_INCLUDED
