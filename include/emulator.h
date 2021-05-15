#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef _6502_EMULATOR_H_
#define _6502_EMULATOR_H_

/* 16 address lines = 2^16 - 1 addresses */
#define MAX_ADDRESS 65535

struct emulator_t {
    /* registers */
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint16_t pc;
    uint8_t sp;
    uint8_t sr;

    /* internal props */
    char* __buf;
    int __bufsize;
    /* the operand set by the various addressing modes */
    uint8_t __operand;
    /* the address set by the various addressing modes */
    uint16_t __addr;
    /* whether an address was set */
    bool __addr_set;

};

struct emulator_t* emu_init(FILE* f);

void emu_run(struct emulator_t* emu, int step);

uint8_t emu_read8(struct emulator_t* emu);
uint16_t emu_read16(struct emulator_t* emu);

void emu_display_state(struct emulator_t* emu);

uint16_t combine_le(uint8_t lo, uint8_t hi);

#endif // _6502_EMULATOR_H_
