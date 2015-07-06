#include <detest/detest.h>

#include <stdio.h>

void test_expect_unexpected_fails() {
    suite_t* suite = create_suite();

    expect(0);

    run_suite(suite);

    expect(get_failure_count(suite) == 1);

    destroy_suite(suite);
}

void test_run_zero_tests_has_zero_failures() {
    suite_t* suite = create_suite();

    run_suite(suite);

    expect(get_failure_count(suite) == 0);

    destroy_suite(suite);
}

int main() {
    add_test(test_expect_unexpected_fails);
    add_test(test_run_zero_tests_has_zero_failures);

    return run_tests();
}
