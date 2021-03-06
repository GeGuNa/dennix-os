/* Copyright (c) 2021 Dennis Wölfing
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

/* libc/src/termios/cfgetispeed.c
 * Get terminal baud rate.
 */

#include <termios.h>

speed_t cfgetispeed(const struct termios* termios) {
    return termios->c_ispeed;
}

speed_t cfgetospeed(const struct termios* termios) {
    return termios->c_ospeed;
}

int cfsetispeed(struct termios* termios, speed_t speed) {
    termios->c_ispeed = speed;
    return 0;
}

int cfsetospeed(struct termios* termios, speed_t speed) {
    termios->c_ospeed = speed;
    return 0;
}
