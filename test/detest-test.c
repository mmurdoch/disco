#include <detest/detest.h>

void test_run_zero_tests_has_zero_failures() {
    suite_t* suite = create_suite();
    silence_suite(suite);

    run_suite(suite);

    expect(get_failure_count(suite) == 0);

    destroy_suite(suite);
}

void expect_unexpected() {
    expect(0);
}

void test_expect_unexpected_fails() {
    suite_t* suite = create_suite();
    silence_suite(suite);

    add_test_to_suite(suite, expect_unexpected);

    run_suite(suite);

    expect(get_failure_count(suite) == 1);

    destroy_suite(suite);
}

void fails() {
    expect(0);
}

void also_fails() {
    expect(0);
}

void test_two_failed_tests() {
    suite_t* suite = create_suite();
    silence_suite(suite);

    add_test_to_suite(suite, fails);
    add_test_to_suite(suite, also_fails);

    run_suite(suite);

    expect(get_failure_count(suite) == 2);

    destroy_suite(suite);
}

int main() {
    add_test(test_run_zero_tests_has_zero_failures);
    add_test(test_expect_unexpected_fails);
    add_test(test_two_failed_tests);

    return run_tests();
}
