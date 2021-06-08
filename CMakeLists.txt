cmake_minimum_required(VERSION 3.1)
project(6502Run VERSION 1.0
    DESCRIPTION "Tiny 6502 emulator written in C."
    LANGUAGES C)
set(SOURCES src/emulator.c src/opcodes.c)

add_executable(6502_run src/6502_run.c ${SOURCES}) 
target_include_directories(6502_run PUBLIC include)
target_compile_definitions(6502_run PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

find_library(CHECK NAMES check) 
find_path(CHECK_INCLUDE_DIRS NAMES check.h)

if (CHECK AND CHECK_INCLUDE_DIRS)
	add_executable(6502_tests tests/util_tests.c ${SOURCES})
	target_include_directories(6502_tests PUBLIC include)
	target_include_directories(6502_tests PUBLIC ${CHECK_INCLUDE_DIRS})
	# libcheck needs extra libraries defined by pkgconfig to build on Linux
	if (UNIX AND NOT APPLE)
		include(FindPkgConfig)
		pkg_check_modules(LIBCHECK REQUIRED check)
		target_link_libraries(6502_tests PRIVATE ${LIBCHECK_LDFLAGS})
	else()
		target_link_libraries(6502_tests ${CHECK})
	endif()
endif()

