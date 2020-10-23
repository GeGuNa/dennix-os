/* Copyright (c) 2018, 2020 Dennis Wölfing
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* kernel/include/dennix/kernel/clock.h
 * System clocks.
 */

#ifndef KERNEL_CLOCK_H
#define KERNEL_CLOCK_H

#include <time.h>

class Clock {
public:
    Clock();
    void add(const Clock* clock);
    int getTime(struct timespec* result);
    int nanosleep(int flags, const struct timespec* requested,
            struct timespec* remaining);
    int setTime(struct timespec* newValue);
    void tick(unsigned long nanoseconds);
public:
    static Clock* get(clockid_t clockid);
    static void onTick(bool user, unsigned long nanoseconds);
private:
    struct timespec value;
};

struct timespec timespecPlus(struct timespec ts1, struct timespec ts2);
bool timespecLess(struct timespec ts1, struct timespec ts2);

#endif
