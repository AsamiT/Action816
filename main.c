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

  typedef struct State65816 {
        uint8_t pc;
        uint8_t sp;
        uint8_t acc;
        uint8_t irx;
        uint8_t iry;
        /** uint8_t carry;
        uint8_t zflag;
        uint8_t irp_dis;
        uint8_t dec_mode;
        uint8_t brkcmd;
        uint8_t overflow;
        uint8_t negflag; **/
        // These are flags set by the processor. Need to review to make sure these are declared right.
        uint8_t *memory;
    } State65816;

    State65816* Init6502(void)
    {
        State65816* state = calloc(1, sizeof(State65816));
        state->memory = malloc(1*sizeof(uint8_t)); //this should have 64 kilobytes allocated
        printf("%d bytes allocated.\n", sizeof(state->memory));
        return state;
    }

    int main(int argc, char**argv) {

        State65816* state = Init6502();
        return 0;
    }

