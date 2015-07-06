#include "time.h"

struct timeval milliseconds_to_timeval(size_t milliseconds) {
    struct timeval t = {0};

    t.tv_sec = milliseconds/1000;
    t.tv_usec = (milliseconds-(1000*t.tv_sec))*1000;

    return t;
}
