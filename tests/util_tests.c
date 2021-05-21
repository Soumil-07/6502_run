#include "check.h"
#include "emulator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_COMBINE_LE(lo, hi, expected)                                      \
    ck_assert_uint_eq(combine_le(lo, hi), expected);

START_TEST(test_utils)
{
    ck_assert_uint_eq(stp_addr(0xff), 0x01ff);
    ck_assert_uint_eq(stp_addr(0xfe), 0x01fe);
    TEST_COMBINE_LE(0xff, 0xab, 0xabff);
    TEST_COMBINE_LE(0x0f, 0xab, 0xab0f);
    TEST_COMBINE_LE(0x00, 0xab, 0xab00);
    TEST_COMBINE_LE(0xff, 0x0b, 0x0bff);
    TEST_COMBINE_LE(0xff, 0x00, 0x00ff);
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
