/* Copyright (c) 2016, 2017, 2018, 2020 Dennis Wölfing
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

/* kernel/include/dennix/fcntl.h
 * File control.
 */

#ifndef _DENNIX_FCNTL_H
#define _DENNIX_FCNTL_H

#define AT_FDCWD (-1)

/* Flags for fstatat(2). */
#define AT_SYMLINK_NOFOLLOW (1 << 0)

/* Flags for linkat(2). */
#define AT_SYMLINK_FOLLOW (1 << 0)

/* Flags for unlinkat(2). */
#define AT_REMOVEDIR (1 << 0)
/* Non standard flag to remove files */
#define AT_REMOVEFILE (1 << 1)

#define F_DUPFD 0
#define F_DUPFD_CLOEXEC 1
#define F_GETFD 2
#define F_SETFD 3
#define F_GETFL 4
#define F_SETFL 5
#define F_DUPFD_CLOFORK 6

#define FD_CLOEXEC (1 << 0)
#define FD_CLOFORK (1 << 1)

#endif
