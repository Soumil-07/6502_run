#include <stdlib.h>
#include "opcodes.h"

/* 0b10000000 */
#define CARRY_SET 0x80

void addr_noop(struct emulator_t* emu)
{

}

void addr_acc(struct emulator_t* emu)
{
    emu->__operand = emu->a;
}

void addr_imp(struct emulator_t* emu)
{

}

void addr_imm(struct emulator_t* emu)
{
    emu->__operand = emu_read8(emu);
}

void addr_abs(struct emulator_t* emu)
{
    emu->__addr = emu_read16(emu);
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_zp(struct emulator_t* emu)
{
    uint16_t idx = combine_le(emu_read8(emu), 0x0);
    emu->__addr = idx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_rel(struct emulator_t* emu)
{

}

void addr_absind(struct emulator_t* emu)
{
    uint8_t idx = emu_read8(emu);
    emu->__operand = combine_le(emu->__buf[idx], emu->__buf[idx + 1]);
    emu->__addr = emu->__operand;
}
void addr_absindx(struct emulator_t* emu)
{
    uint16_t idx = emu_read16(emu);
    idx += emu->x;
    emu->__addr = idx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_absindy(struct emulator_t* emu)
{
    uint16_t idx = emu_read16(emu);
    idx += emu->y;
    emu->__addr = idx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_zpx(struct emulator_t* emu)
{
    uint16_t zpidx = combine_le(emu_read8(emu), 0x0);
    zpidx += emu->x;
    emu->__addr = zpidx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_zpy(struct emulator_t* emu)
{
    uint16_t zpidx = combine_le(emu_read8(emu), 0x0);
    zpidx += emu->y;
    emu->__addr = zpidx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_zpix(struct emulator_t* emu)
{
    // TODO
}

void addr_zpiy(struct emulator_t* emu)
{
    // TODO
}

void lda(struct emulator_t* emu)
{
    emu->a = emu->__operand;
}

void ldx(struct emulator_t* emu)
{
    emu->x = emu->__operand;
}

void ldy(struct emulator_t* emu)
{
    emu->y = emu->__operand;
}

void sta(struct emulator_t* emu)
{
    emu->__buf[emu->__addr] = emu->a;
}

void stx(struct emulator_t* emu)
{
    emu->__buf[emu->__addr] = emu->x;
}
void sty(struct emulator_t* emu)
{
    emu->__buf[emu->__addr] = emu->y;
}

void adc(struct emulator_t* emu)
{
    uint8_t op1 = emu->a;
    uint8_t op2 = emu->__operand;
    emu->a += emu->__operand;

    /* overflow occurred */
    if (op1 > emu->a || op2 > emu->a)
        emu->sr |= CARRY_SET;
}

void sbc(struct emulator_t* emu)
{
    /* TODO */
}

void inc(struct emulator_t* emu)
{
    emu->__buf[emu->__addr]++;
}

void inx(struct emulator_t* emu)
{
    emu->x++;
}

void iny(struct emulator_t* emu)
{
    emu->y++;
}

void dec(struct emulator_t* emu)
{
    emu->__buf[emu->__addr]--;
}

void dex(struct emulator_t* emu)
{
    emu->x--;
}

void dey(struct emulator_t* emu)
{
    emu->y--;
}

void brk(struct emulator_t* emu)
{
    emu_display_state(emu);
    exit(0);
}
