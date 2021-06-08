#include "emulator.h"
#include <stdio.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG 0
#endif // DEBUG

int main(int argc, char** argv)
{
    char* filename;
    if (argc < 2)
    {
	printf("USAGE: 6502_run FILE...\n");
	return 1;
    }

    FILE* fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
	perror("fopen");
	return 1;
    }

    struct emulator_t* emu = emu_init(fp);
    emu_run(emu, DEBUG);

    fclose(fp);
}
