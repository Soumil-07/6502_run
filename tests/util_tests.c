#include "check.h"
#include "emulator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_COMBINE_LE(lo, hi, expected)                                      \
    ck_assert_uint_eq(combine_le(lo, hi), expected);

#define TEST_STP_ADDR(addr, expected)                                          \
    ck_assert_uint_eq(stp_addr(addr), expected)

#define TEST_LROTATE(n, expected) ck_assert_uint_eq(lrotate(n), expected)

START_TEST(test_utils)
{
    TEST_STP_ADDR(0xff, 0x01ff);
    TEST_STP_ADDR(0x0f, 0x010f);
    TEST_STP_ADDR(0xf0, 0x01f0);
    TEST_COMBINE_LE(0xff, 0xab, 0xabff);
    TEST_COMBINE_LE(0x0f, 0xab, 0xab0f);
    TEST_COMBINE_LE(0x00, 0xab, 0xab00);
    TEST_COMBINE_LE(0xff, 0x0b, 0x0bff);
    TEST_COMBINE_LE(0xff, 0x00, 0x00ff);
    TEST_LROTATE(0b100, 0b1000);
    TEST_LROTATE(0b10101110, 0b01011101);
    TEST_LROTATE(0b10111, 0b101110);
}
END_TEST

Suite* test_suite()
{
    Suite* s;
    TCase* tc_core;

    s = suite_create("6502_tests");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_utils);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
