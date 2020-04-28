/* Copyright (c) 2020 Dennis Wölfing
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

/* kernel/include/dennix/kernel/bga.h
 * Bochs Graphics Adaptor.
 */

#ifndef KERNEL_BGA_H
#define KERNEL_BGA_H

#include <dennix/kernel/display.h>

class BgaDevice : public GraphicsDriver {
public:
    BgaDevice(uint16_t version, uint8_t bus, uint8_t device, uint8_t function);
    virtual bool isSupportedMode(video_mode mode);
    virtual vaddr_t setVideoMode(video_mode* mode);
public:
    static void initialize(uint8_t bus, uint8_t device, uint8_t function);
private:
    vaddr_t framebuffer;
    uint16_t version;
    uint16_t maxX;
    uint16_t maxY;
    uint8_t bus;
    uint8_t device;
    uint8_t function;
};

#endif