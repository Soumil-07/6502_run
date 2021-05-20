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
/* Loads and stores */
void lda(struct emulator_t* emu);
void ldy(struct emulator_t* emu);
void sta(struct emulator_t* emu);
void stx(struct emulator_t* emu);
void sty(struct emulator_t* emu);
void adc(struct emulator_t* emu);
void sbc(struct emulator_t* emu);
/* increments and decrements */
void inc(struct emulator_t* emu);
void inx(struct emulator_t* emu);
void iny(struct emulator_t* emu);
void dec(struct emulator_t* emu);
void dex(struct emulator_t* emu);
void dey(struct emulator_t* emu);
/* shifting and rotating */
void asl(struct emulator_t* emu);
void lsr(struct emulator_t* emu);
void rol(struct emulator_t* emu);
void ror(struct emulator_t* emu);
/* logic */
void op_and(struct emulator_t* emu);
void ora(struct emulator_t* emu);
void eor(struct emulator_t* emu);
/* comparison */
void cmp(struct emulator_t* emu);
void cpx(struct emulator_t* emu);
void cpy(struct emulator_t* emu);
void bit(struct emulator_t* emu);
/* branches */
void bcc(struct emulator_t* emu);
void bcs(struct emulator_t* emu);
void bne(struct emulator_t* emu);
void beq(struct emulator_t* emu);
void bpl(struct emulator_t* emu);
void bmi(struct emulator_t* emu);
void bvc(struct emulator_t* emu);
void bvs(struct emulator_t* emu);
/* transferring */
void tax(struct emulator_t* emu);
void txa(struct emulator_t* emu);
void tay(struct emulator_t* emu);
void tya(struct emulator_t* emu);
void tsx(struct emulator_t* emu);
void txs(struct emulator_t* emu);
/* stack */
void pha(struct emulator_t* emu);
void pla(struct emulator_t* emu);
void php(struct emulator_t* emu);
void plp(struct emulator_t* emu);
/* subroutines */
void jmp(struct emulator_t* emu);
void jsr(struct emulator_t* emu);
void rts(struct emulator_t* emu);
void rti(struct emulator_t* emu);
/* set and clear ops */
void clc(struct emulator_t* emu);
void sec(struct emulator_t* emu);
void cld(struct emulator_t* emu);
void sed(struct emulator_t* emu);
void cli(struct emulator_t* emu);
void sei(struct emulator_t* emu);
void clv(struct emulator_t* emu);
/* misc */
void nop(struct emulator_t* emu);
void brk(struct emulator_t* emu);

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
    {addr_acc, asl},
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
    {addr_zpix, op_and},
    {},
    {},
    {},
    {addr_zp, op_and},
    {},
    {},
    {},
    {addr_imm, op_and},
    {},
    {},
    {},
    {addr_abs, op_and},
    {},
    {},

    /* 30-3F */
    {},
    {addr_zpiy, op_and},
    {},
    {},
    {},
    {addr_zpx, op_and},
    {},
    {},
    {},
    {addr_absindy, op_and},
    {},
    {},
    {},
    {addr_absindx, op_and},
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
    {addr_noop, pha},
    {},
    {addr_acc, lsr},
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
    {addr_noop, pla},
    {addr_imm, adc},
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
    {addr_imp, inx},
    {},
    {addr_imp, txa},
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
    {addr_imp, tya},
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
    {addr_imp, tay},
    {addr_imm, lda},
    {addr_imp, tax},
    {},
    {},
    {},
    {},
    {},

    /* B0-Bf */
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

    /* C0-Bf */
    {},
    {},
    {},
    {},
    {},
    {addr_abs, cmp},
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
};

#endif // _6502_OPCODES_H_
