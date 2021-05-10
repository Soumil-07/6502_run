cmake_minimum_required(VERSION 3.1)
project(6502Run VERSION 1.0
    DESCRIPTION "Tiny 6502 emulator written in C."
    LANGUAGES C)
add_executable(6502_run src/6502_run.c src/emulator.c src/opcodes.c)
target_include_directories(6502_run PUBLIC include)
target_compile_definitions(6502_run PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")
