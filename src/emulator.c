#include "emulator.h"
#include "opcodes.h"
#include <assert.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define RSB_LO 0xfffc
#define RSB_HI 0xfffd
#define NMIB_LO 0xfffa
#define NMIB_HI 0xfffb
/* 0b00100000 - the bit 5 is always set */
#define SR_INITIAL 0x20

/* printing 0b hack */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
    (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'),                      \
        (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),                  \
        (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),                  \
        (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

struct emulator_t* emu_init(FILE* f)
{
    /* read 2^16 + 1 bits in memory, since the 6502 has only 16 address lines */
    char* buf;
    size_t bufsize;
    fseek(f, 0, SEEK_END);
    bufsize = ftell(f);

    if (bufsize < MAX_ADDRESS + 1)
    {
	printf("the input file should be %d bytes long\n", MAX_ADDRESS + 1);
	exit(1);
    }
    buf = (char*)malloc(bufsize);
    rewind(f);

    if (fread(buf, bufsize, 1, f) != 1)
    {
	perror("fread");
	exit(1);
    }

    struct emulator_t* emu =
        (struct emulator_t*)malloc(sizeof(struct emulator_t));
    emu->sp = 0xff;
    emu->sr = SR_INITIAL;
    emu->__buf = buf;
    emu->__bufsize = bufsize;

    /* get the starting vector from the reset bits and jump to it */
    assert(emu->__bufsize > 0xfffd && "check binary size");
    uint16_t st_vec = combine_le(emu->__buf[RSB_LO], emu->__buf[RSB_HI]);
    emu->pc = st_vec;
    /* the 6502 takes 7 clock cycles to initialize */
    emu->clc = 7;

    return emu;
}

void emu_run(struct emulator_t* emu, int debug)
{
    while (emu->pc < MAX_ADDRESS)
    {
	uint8_t opcode = emu_read8(emu);
	opcode_t op = opcodes[opcode];

	if (op.run_op == 0x0)
	{
	    printf("the opcode %02x is not supported currently\n", opcode);
	    emu_display_state(emu);
	    exit(1);
	}

	emu->__addr_set = 0;
	op.addr_mode(emu);
	op.run_op(emu);
	emu->clc += op.clc;

	/* in "debug" mode, wait for a keypress before continuing */
	if (debug)
	{
	    emu_display_state(emu);
	    char c;
	    scanf("%c", &c);
	    if (c == 'i')
	    {
		emu_nmib(emu);
	    }
	}
    }

    emu_display_state(emu);
}

void emu_irqb(struct emulator_t* emu)
{
    // Push the PC and SR onto the stack
    emu->__buf[stp_addr(emu->sp--)] = emu->pc;
    emu->__buf[stp_addr(emu->sp--)] = emu->sr;
}

void emu_nmib(struct emulator_t* emu)
{
    // Push the PC and SR onto the stack
    emu->__buf[stp_addr(emu->sp--)] = emu->pc;
    emu->__buf[stp_addr(emu->sp--)] = emu->sr;

    emu->pc = combine_le(emu->__buf[NMIB_LO], emu->__buf[NMIB_HI]);
}

uint8_t emu_read8(struct emulator_t* emu)
{
    /* bounds checking */
    if (emu->pc == MAX_ADDRESS)
    {
	printf("eof\n");
	exit(1);
    }
    return emu->__buf[emu->pc++];
}

uint16_t emu_read16(struct emulator_t* emu)
{
    return combine_le(emu_read8(emu), emu_read8(emu));
}

void emu_display_state(struct emulator_t* emu)
{
    printf(
        "A=$%02x X=$%02x Y=$%02x PC=$%04x SP=$%04x SR=0b" BYTE_TO_BINARY_PATTERN
        " CLC=%llu\n",
        emu->a, emu->x, emu->y, emu->pc, emu->sp, BYTE_TO_BINARY(emu->sr),
        emu->clc);
}

uint16_t combine_le(uint8_t lo, uint8_t hi) { return (hi << 8) | lo; }

uint16_t stp_addr(uint8_t addr) { return combine_le(addr, 0x1); }

uint8_t lrotate(uint8_t n) { return n << 1 | n >> 7; }

uint8_t rrotate(uint8_t n);
