#include <assert.h>
#include <stdio.h>

#include "emulator.h"

// TODO: add proper unit tests
int main() { assert(stp_addr(0xff) == 0x01ff); }
