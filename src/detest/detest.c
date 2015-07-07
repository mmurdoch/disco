#include "detest.h"

#include <stdio.h>

suite_t* current_suite;

test_function_node_t* create_test_function_node(void (*test_function)()) {
    test_function_node_t* node = (test_function_node_t*)
        malloc(sizeof(test_function_node_t));
    if (node == NULL) {
        return NULL;
    }
    node->test_function = test_function;
    node->next = NULL;

    return node;
}

void add_test(void (*test_function)()) {
    if (current_suite == NULL) {
        current_suite = create_suite();
    }

    test_function_node_t* node = create_test_function_node(test_function);
    if (current_suite->head == NULL) {
        current_suite->head = node;
    } else {
        test_function_node_t* current = current_suite->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

int run_tests() {
    run_suite(current_suite);

    int failures = get_failure_count(current_suite);

    destroy_suite(current_suite);

    return failures;
}

void check_expectation(int expected, const char* filename, int line_number) {
    if (!expected) {
        if (!current_suite->silent) {
            printf("Failure at %s:%d\n", filename, line_number);
        }

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

void add_test_to_suite(suite_t* suite, void (*test_function)()) {
    suite_t* old_suite = current_suite;
    current_suite = suite;

    add_test(test_function);

    current_suite = old_suite;
}

void silence_suite(suite_t* suite) {
    suite->silent = 1;
}

void run_suite(suite_t* suite) {
    suite_t* old_suite = current_suite;
    current_suite = suite;

    test_function_node_t* node = current_suite->head;
    while (node != NULL) {
        node->test_function();
        node = node->next;
    }

    current_suite = old_suite;
}

size_t get_failure_count(suite_t* suite) {
    return suite->failure_count;
}

void destroy_test_function_node(test_function_node_t* node) {
    if (node != NULL) {
        destroy_test_function_node(node->next);
    }

    free(node);
}

void destroy_suite(suite_t* suite) {
    test_function_node_t* node = suite->head;
    destroy_test_function_node(node);

    free(suite);
}
