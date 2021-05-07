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

/* libc/src/unistd/fpathconf.c
 * Get pathname configuration variables.
 */

#include <limits.h>
#include <unistd.h>
#include <sys/syscall.h>

DEFINE_SYSCALL(SYSCALL_FPATHCONF, long, sys_fpathconf, (int, int));

long fpathconf(int fd, int name) {
    switch (name) {
    case _PC_FILESIZEBITS: return FILESIZEBITS;
    case _PC_PATH_MAX: return -1; // unlimited
    case _PC_PIPE_BUF: return PIPE_BUF;
    case _PC_2_SYMLINKS: return _POSIX2_SYMLINKS;
    case _PC_NO_TRUNC: return _POSIX_NO_TRUNC;
    case _PC_VDISABLE: return _POSIX_VDISABLE;
    default:
        return sys_fpathconf(fd, name);
    }
}
