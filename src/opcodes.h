#ifndef _6502_OPCODES_H_
#define _6502_OPCODES_H_

#include "emulator.h"

typedef struct 
{
    void (*addr_mode) (struct emulator_t*);
    void (*run_op) (struct emulator_t*);
} opcode_t;

/* addressing modes */
void addr_acc(struct emulator_t* emu);
void addr_imp(struct emulator_t* emu);
void addr_imm(struct emulator_t* emu);
void addr_abs(struct emulator_t* emu);
void addr_zp(struct emulator_t* emu);
void addr_rel(struct emulator_t* emu);
void addr_absind(struct emulator_t* emu);
void addr_absindx(struct emulator_t* emu);
void addr_absindy(struct emulator_t* emu);
void addr_zpx(struct emulator_t* emu);
void addr_zpy(struct emulator_t* emu);
void addr_zpix(struct emulator_t* emu);
void addr_zpiy(struct emulator_t* emu);
/* noop addr_mode for brk */
void addr_noop(struct emulator_t* emu);

/* operations */
void brk(struct emulator_t* emu);
void lda(struct emulator_t* emu);

static opcode_t opcodes[256] = {
    /* 00-0F */
    {addr_noop, brk},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* 10-1F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* 20-2F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* 30-3F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* 40-4F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* 50-5F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    
    /* 60-6F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* 70-7F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    
    /* 80-8F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* 90-9F */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},

    /* A0-AF */
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {addr_imm, lda},
    {},
    {},
    {},
    {},
    {},
    {},
};

#endif // _6502_OPCODES_H_
