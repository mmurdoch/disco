#ifndef DETEST_H
#define DETEST_H

#include <stdlib.h>
#include <string.h>

#define test(test_name) void test_##test_name()

typedef struct {
    void (*test_function)();
    size_t failure_count;
} suite_t;

void expect(int expected);
void add_test(void (*test_function)());
int run_tests();

suite_t* create_suite();
void run_suite(suite_t* suite);
size_t get_failure_count(suite_t* suite);
void destroy_suite(suite_t* suite);

#endif // DETEST_H
