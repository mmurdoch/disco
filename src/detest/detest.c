#include "detest.h"

suite_t* current_suite;

void add_test(void (*test_function)()) {
    if (current_suite == NULL) {
        current_suite = create_suite();
    }

    current_suite->test_function = test_function;
}

int run_tests() {
    run_suite(current_suite);

    int failures = get_failure_count(current_suite);

    destroy_suite(current_suite);

    return failures;
}

void expect(int expected) {
    if (!expected) {
        current_suite->failure_count++;
    }
}

suite_t* create_suite() {
    suite_t* suite = (suite_t*) malloc(sizeof(suite_t));
    if (suite == NULL) {
        return NULL;
    }

    memset(suite, 0, sizeof(suite_t));

    return suite;
}

void run_suite(suite_t* suite) {
    suite_t* old_suite = current_suite;
    current_suite = suite;

    if (current_suite->test_function != NULL) {
        current_suite->test_function();
    }

    current_suite = old_suite;
}

size_t get_failure_count(suite_t* suite) {
    return suite->failure_count;
}

void destroy_suite(suite_t* suite) {
    free(suite);
}
