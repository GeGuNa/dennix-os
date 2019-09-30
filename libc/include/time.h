/* Copyright (c) 2016, 2018, 2019 Dennis Wölfing
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

/* libc/include/time.h
 * Time declarations.
 */

#ifndef _TIME_H
#define _TIME_H

#include <sys/cdefs.h>
#define __need_clock_t
#define __need_locale_t
#define __need_NULL
#define __need_size_t
#define __need_time_t
#if __USE_DENNIX || __USE_POSIX
#  define __need_clockid_t
#  define __need_timer_t
#endif
#include <bits/types.h>
#include <dennix/timespec.h>
#if __USE_DENNIX || __USE_POSIX
#  include <dennix/clock.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCKS_PER_SEC ((clock_t) 1000000)

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

char* asctime(const struct tm*);
clock_t clock(void);
char* ctime(const time_t*);
struct tm* gmtime(const time_t*);
struct tm* localtime(const time_t*);
time_t mktime(struct tm*);
size_t strftime(char* __restrict, size_t, const char* __restrict,
        const struct tm* __restrict);
time_t time(time_t*);

#if __USE_DENNIX || __USE_POSIX
extern int daylight;
extern long timezone;
extern char* tzname[2];

int clock_gettime(clockid_t, struct timespec*);
int clock_nanosleep(clockid_t, int, const struct timespec*, struct timespec*);
struct tm* gmtime_r(const time_t* __restrict, struct tm* __restrict);
int nanosleep(const struct timespec*, struct timespec*);
void tzset(void);
#endif

#if __USE_DENNIX
extern long altzone;

time_t timegm(struct tm*);
#endif

#ifdef __cplusplus
}
#endif

#endif
