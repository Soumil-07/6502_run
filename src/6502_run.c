#include <stdio.h>
#include "emulator.h"

#ifndef DEBUG
#define DEBUG 0
#endif // DEBUG

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("USAGE: 6502_run FILE...");
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
