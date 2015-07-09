#ifndef DISCO_TIME_H
#define DISCO_TIME_H

#include <stdlib.h>

/**
 * Converts a number of milliseconds to a timeval structure.
 *
 * @param milliseconds the number of milliseconds to convert
 * @return converted timeval structure
 */
struct timeval milliseconds_to_timeval(size_t milliseconds);

/**
 * Converts a number of milliseconds to a timespec structure.
 *
 * @param milliseconds the number of milliseconds to convert
 * @return converted timespec structure
 */
struct timespec milliseconds_to_timespec(size_t milliseconds);

/**
 * Suspends thread execution for a number of milliseconds.
 *
 * @param milliseconds the number of milliseconds to suspend the thread for
 */
void sleep_milliseconds(size_t milliseconds);

#endif // DISCO_TIME_H
