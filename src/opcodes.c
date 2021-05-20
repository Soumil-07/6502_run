#include "opcodes.h"
#include <stdlib.h>

#define CARRY_SET 0x1
#define SET_LT 0x80 // 0b10000000
#define SET_EQ 0x3  // 0b00000011
#define SET_GT 0x1  // 0b00000001

void addr_noop(struct emulator_t* emu) {}

void addr_acc(struct emulator_t* emu) { emu->__operand = emu->a; }

void addr_imp(struct emulator_t* emu) {}

void addr_imm(struct emulator_t* emu) { emu->__operand = emu_read8(emu); }

void addr_abs(struct emulator_t* emu)
{
    emu->__addr_set = true;
    emu->__addr = emu_read16(emu);
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_zp(struct emulator_t* emu)
{
    uint16_t idx = combine_le(emu_read8(emu), 0x0);
    emu->__addr_set = true;
    emu->__addr = idx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_rel(struct emulator_t* emu) {}

void addr_absind(struct emulator_t* emu)
{
    uint8_t idx = emu_read8(emu);
    emu->__operand = combine_le(emu->__buf[idx], emu->__buf[idx + 1]);
    emu->__addr_set = true;
    emu->__addr = emu->__operand;
}
void addr_absindx(struct emulator_t* emu)
{
    uint16_t idx = emu_read16(emu);
    idx += emu->x;
    emu->__addr_set = true;
    emu->__addr = idx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_absindy(struct emulator_t* emu)
{
    uint16_t idx = emu_read16(emu);
    idx += emu->y;
    emu->__addr_set = true;
    emu->__addr = idx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_zpx(struct emulator_t* emu)
{
    uint16_t zpidx = combine_le(emu_read8(emu), 0x0);
    zpidx += emu->x;
    emu->__addr_set = true;
    emu->__addr = zpidx;
    emu->__operand = emu->__buf[emu->__addr];
}

void addr_zpy(struct emulator_t* emu)
{
    uint16_t zpidx = combine_le(emu_read8(emu), 0x0);
    zpidx += emu->y;
    emu->__addr_set = true;
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

void lda(struct emulator_t* emu) { emu->a = emu->__operand; }

void ldx(struct emulator_t* emu) { emu->x = emu->__operand; }

void ldy(struct emulator_t* emu) { emu->y = emu->__operand; }

void sta(struct emulator_t* emu) { emu->__buf[emu->__addr] = emu->a; }

void stx(struct emulator_t* emu) { emu->__buf[emu->__addr] = emu->x; }
void sty(struct emulator_t* emu) { emu->__buf[emu->__addr] = emu->y; }

void tax(struct emulator_t* emu) { emu->x = emu->a; }

void txa(struct emulator_t* emu) { emu->a = emu->x; }

void tay(struct emulator_t* emu) { emu->y = emu->a; }

void tya(struct emulator_t* emu) { emu->a = emu->y; }

void tsx(struct emulator_t* emu)
{ /* TODO */
}

void txs(struct emulator_t* emu)
{ /* TODO */
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
{ /* TODO */
}

void inc(struct emulator_t* emu) { emu->__buf[emu->__addr]++; }

void inx(struct emulator_t* emu) { emu->x++; }

void iny(struct emulator_t* emu) { emu->y++; }

void dec(struct emulator_t* emu) { emu->__buf[emu->__addr]--; }

void dex(struct emulator_t* emu) { emu->x--; }

void dey(struct emulator_t* emu) { emu->y--; }

void asl(struct emulator_t* emu)
{
    uint8_t shifted = emu->__operand << 1;
    /* get the left-most bit */
    if (emu->__operand & 0x80 >> 7)
	emu->sr |= CARRY_SET;
    else
	/* ANDing with 0b11111110 changes the last bit to 0 and keeps everything
	 * else the same */
	emu->sr &= 0xfe;

    /* asl either modifies addresses directly, or the accumulator */
    if (emu->__addr_set)
	emu->__buf[emu->__addr] = shifted;
    else
	emu->a = shifted;
}

void lsr(struct emulator_t* emu)
{
    uint8_t shifted = emu->__operand >> 1;
    /* get the right-most bit */
    if (emu->__operand & 0x1)
	emu->sr |= CARRY_SET;
    else
	emu->sr &= 0xfe;

    /* asl either modifies addresses directly, or the accumulator */
    if (emu->__addr_set)
	emu->__buf[emu->__addr] = (uint8_t)shifted;
    else
	emu->a = (uint8_t)shifted;
}

void op_and(struct emulator_t* emu) { emu->a &= emu->__operand; }

void cmp(struct emulator_t* emu)
{
    if (emu->a > emu->__operand)
	emu->sr |= SET_GT;
    else if (emu->__operand == emu->a)
	emu->sr |= SET_EQ;
    else
	emu->sr |= SET_LT;
}

void pha(struct emulator_t* emu)
{
    if (emu->sp == 0x0)
    {
	printf("fatal: stack overflow\n");
	exit(EXIT_FAILURE);
    }
    emu->__buf[stp_addr(emu->sp--)] = emu->a;
}

void pla(struct emulator_t* emu)
{
    if (emu->sp == 0xff)
    {
	printf("fatal: stack empty\n");
	exit(EXIT_FAILURE);
    }
    emu->a = emu->__buf[stp_addr(++emu->sp)];
}

void brk(struct emulator_t* emu)
{
    emu_display_state(emu);
    exit(0);
}
