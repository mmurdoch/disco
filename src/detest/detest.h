#ifndef DETEST_H
#define DETEST_H

#include <stdlib.h>
#include <string.h>

#define expect(expected) check_expectation((expected), __FILE__, __LINE__)

typedef struct test_function_node_t test_function_node_t;

struct test_function_node_t {
    void (*test_function)();
    test_function_node_t* next;
};

typedef struct {
    test_function_node_t* head;
    size_t failure_count;
    int silent;
} suite_t;

void check_expectation(int expected, const char* filename, int line_number);
void add_test(void (*test_function)());
int run_tests();

suite_t* create_suite();
void add_test_to_suite(suite_t* suite, void (*test_function)());
void silence_suite(suite_t* suite);
void run_suite(suite_t* suite);
size_t get_failure_count(suite_t* suite);
void destroy_suite(suite_t* suite);

#endif // DETEST_H
