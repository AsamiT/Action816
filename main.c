/**

  Action816 - A custom 65816 emulator
  (c) 2018, James Maloy and Jeremy Brown, all rights reserved
  Licensed under the MIT license.

  file: main.c
  desc: "Base for which we invent the universe."
  date: 13 April 2018

  **/

  #include <stdlib.h>
  #include <stdio.h>
  #include <stdint.h>
  #include "SDL2\SDL.h"

  typedef struct sys_Flags { /* note: this is not finished */
        uint8_t carry; //Carry flag
        uint8_t zflag; //Zero flag
        uint8_t irp_dis; //Interrupt Disable
        uint8_t dec_mode; //Decimal mode
        uint8_t brkcmd; //Break Command
        uint8_t overflow; //Overflow flag
        uint8_t negflag; //Negative flag
        } sys_Flags;

  typedef struct State65816 {
        uint8_t pc; //Program Counter
        uint8_t sp; // Stack Pointer
        uint8_t acc; //Accumulator
        uint8_t irx; //Index Register X
        uint8_t iry; //Index Register Y
        uint8_t *memory; //Memory allocation

    } State65816;

    State65816* Init6502(void)
    {
        gen_window();
        size_t mem_size = 0x10000;
        State65816* state = calloc(1, sizeof(State65816));
        state->memory = malloc(mem_size); //this should have 64 kilobytes allocated
        printf("%d bytes allocated.\n", _msize(state->memory)); //and it does
        return state;
    }

    int main(int argc, char**argv) {

        State65816* state = Init6502();
        return 0;
    }

