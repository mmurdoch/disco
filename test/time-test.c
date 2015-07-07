#include <stdlib.h>
#include <time.h>

#include <detest/detest.h>
#include <disco/time.h>

void test_zero_milliseconds_to_timeval() {
    size_t milliseconds = 0;

    struct timeval t = milliseconds_to_timeval(milliseconds);

    expect(t.tv_sec == 0 && t.tv_usec == 0);
}

void test_one_millisecond_to_timeval() {
    size_t milliseconds = 1;

    struct timeval t = milliseconds_to_timeval(milliseconds);

    expect(t.tv_sec == 0 && t.tv_usec == 1000);
}

void test_one_thousand_milliseconds_to_timeval() {
    size_t milliseconds = 1000;

    struct timeval t = milliseconds_to_timeval(milliseconds);

    expect(t.tv_sec == 1 && t.tv_usec == 0);
}

void test_one_thousand_and_one_milliseconds_to_timeval() {
    size_t milliseconds = 1001;

    struct timeval t = milliseconds_to_timeval(milliseconds);

    expect(t.tv_sec == 1 && t.tv_usec == 1000);
}

int main() {
    add_test(test_zero_milliseconds_to_timeval);
    add_test(test_one_millisecond_to_timeval);
    add_test(test_one_thousand_milliseconds_to_timeval);
    add_test(test_one_thousand_and_one_milliseconds_to_timeval);

    return run_tests();
}
