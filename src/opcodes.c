#include <stdlib.h>
#include "opcodes.h"

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
    emu->__operand = emu->__buf[emu_read16(emu)];
}

void addr_zp(struct emulator_t* emu)
{
    uint16_t idx = combine_le(emu_read8(emu), 0x0);
    emu->__operand = emu->__buf[idx];
}

void addr_rel(struct emulator_t* emu)
{

}

void addr_absind(struct emulator_t* emu)
{
    uint8_t idx = emu_read8(emu);
    emu->__operand = combine_le(emu->__buf[idx], emu->__buf[idx + 1]);
}
void addr_absindx(struct emulator_t* emu)
{
    uint16_t idx = emu_read16(emu);
    idx += emu->x;
    emu->__operand = emu->__buf[idx];
}

void addr_absindy(struct emulator_t* emu)
{
    uint16_t idx = emu_read16(emu);
    idx += emu->y;
    emu->__operand = emu->__buf[idx];
}

void addr_zpx(struct emulator_t* emu)
{
    uint16_t zpidx = combine_le(emu_read8(emu), 0x0);
    zpidx += emu->x;
    emu->__operand = emu->__buf[zpidx];
}

void addr_zpy(struct emulator_t* emu)
{
    uint16_t zpidx = combine_le(emu_read8(emu), 0x0);
    zpidx += emu->y;
    emu->__operand = emu->__buf[zpidx];
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

void brk(struct emulator_t* emu)
{
    emu_display_state(emu);
    exit(0);
}
