#include "time.h"

#include <time.h>

struct timeval milliseconds_to_timeval(size_t milliseconds) {
    struct timeval t = {0};

    t.tv_sec = milliseconds/1000;
    t.tv_usec = (milliseconds-(1000*t.tv_sec))*1000;

    return t;
}

/**
 * Converts a number of milliseconds to a timespec structure.
 *
 * @param milliseconds the number of milliseconds to convert
 * @return converted timespec structure
 */
struct timespec milliseconds_to_timespec(size_t milliseconds) {
    struct timespec t = {0};

    t.tv_sec = milliseconds/1000;
    t.tv_nsec = (milliseconds-(1000*t.tv_sec))*1000000;

    return t;
}

void sleep_milliseconds(size_t milliseconds) {
    struct timespec sleep_time = milliseconds_to_timespec(milliseconds);
    nanosleep(&sleep_time, NULL);
}
