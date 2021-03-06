#include "emulator.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDRESS 65535
/* printing 0b hack */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
    (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'),                      \
        (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),                  \
        (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),                  \
        (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

void emu_display_state(struct emulator_t* emu)
{
    printf(
        "A=$%02x X=$%02x Y=$%02x PC=$%04x SP=$%04x SR=0b" BYTE_TO_BINARY_PATTERN
        " CLC=%llu\n",
        emu->a, emu->x, emu->y, emu->pc, emu->sp, BYTE_TO_BINARY(emu->sr),
        emu->clc);
}

void parseopt(int argc, char** argv, char** filename, int* debug);

int main(int argc, char** argv)
{
    char* filename;
    int debug;
    if (argc < 2)
    {
	printf("USAGE: 6502_run FILE...\n");
	return 1;
    }

    parseopt(argc, argv, &filename, &debug);

    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
	perror("fopen");
	return 1;
    }

    struct emulator_t* emu = emu_init(fp);
    // emu_run(emu, DEBUG);
    while (emu->pc < MAX_ADDRESS)
    {
	emu_step(emu);
	// check if the BRK flag was set
	if (emu->sr & 0x10)
	{
	    break;
	}

	if (debug)
	{
	    char c;
	    emu_display_state(emu);

	    scanf("%c", &c);
	    if (c == 'i')
	    {
		emu_nmib(emu);
	    }
	}
    }

    emu_display_state(emu);
    fclose(fp);
    exit(EXIT_SUCCESS);
}

void parseopt(int argc, char** argv, char** filename, int* debug)
{
    *debug = 0;
    if (argc == 2)
    {
	*filename = argv[1];
	return;
    }

    if (strcmp(argv[1], "-d") == 0)
    {
	*debug = 1;
	*filename = argv[2];
    }

    else if (strcmp(argv[2], "-d") == 0)
    {
	*debug = 1;
	*filename = argv[1];
    }

    else
    {
	printf("unexpected number of arguments: %d\n", argc - 1);
	exit(EXIT_FAILURE);
    }
}
