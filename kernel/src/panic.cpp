/* Copyright (c) 2019 Dennis Wölfing
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

/* kernel/src/panic.cpp
 * Kernel panic.
 */

#include <dennix/kernel/log.h>
#include <dennix/kernel/panic.h>
#include <dennix/kernel/registers.h>
#include <dennix/kernel/terminaldisplay.h>

static void panic(const char* file, unsigned int line, const char* func,
        const char* format, va_list ap) {
    Interrupts::disable();
    Log::printf("\n\e[1;37;41mKERNEL PANIC\n");
    Log::vprintf(format, ap);
    Log::printf("\nat %s (%s:%u)\n", func, file, line);
}

NORETURN void panic(const char* file, unsigned int line, const char* func,
        const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    panic(file, line, func, format, ap);
    va_end(ap);

    TerminalDisplay::display->update();
    while (true) asm ("hlt");
}

NORETURN void panic(const char* file, unsigned int line, const char* func,
        const InterruptContext* context, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    panic(file, line, func, format, ap);
    va_end(ap);
    Registers::dumpInterruptContext(context);

    TerminalDisplay::display->update();
    while (true) asm ("hlt");
}
