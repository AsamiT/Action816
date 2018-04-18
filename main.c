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
        uint8_t pc; //Program Counter
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
        uint8_t *memory; //Memory allocation
    } State65816;

    /**
     * reset6502 - resets the processor to the power on state for 6502 Emulation mode
     * @param instance instance of the emulated CPU to reset.
     */
    void reset6502(State65816 *instance) {
      instance->pc = 0xFFFC;
      instance->sysFlags = 0b00000100; //binary set, disable decimal mode, enable IRQ disable
      instance->sp = null; //suggestions on what goes here?
      instance->sysFlags = 0b00001000; //binary set, enable decimal mode
      /* this is done based on suggestion from https://goo.gl/kgvkRk;
        demonstrating the process in which a 6502 processor initializes. */
    }

      /**
      * Init6502 - initial "initialization" of the processor function for 6502 Emulation mode.
      * @param void
      * @return a valid CPU state object.
      */
    State65816* Init6502(void)
    {
        size_t mem_size = 0x10000;
        State65816* state = calloc(1, sizeof(State65816));
        state->memory = malloc(mem_size); //this should have 64 kilobytes allocated
        printf("%d bytes allocated.\n", _msize(state->memory)); //and it does
        reset6502(state); //invoke a reset
        return state;
    }

    int main(int argc, char**argv) {
        State65816* state = Init6502();
        return 0;
    }
