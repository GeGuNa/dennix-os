/* Copyright (c) 2019, 2021 Dennis Wölfing
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

/* kernel/include/dennix/kernel/devices.h
 * Devices.
 */

#ifndef KERNEL_DEVICES_H
#define KERNEL_DEVICES_H

#include <dennix/kernel/directory.h>

class DevFS : public DirectoryVnode {
public:
    DevFS();
    void addDevice(const char* name, const Reference<Vnode>& vnode);
    void initialize(const Reference<DirectoryVnode>& rootDir);
    int link(const char* name, const Reference<Vnode>& vnode) override;
    int mkdir(const char* name, mode_t mode) override;
    Reference<Vnode> open(const char* name, int flags, mode_t mode) override;
    int rename(const Reference<Vnode>& oldDirectory, const char* oldName,
            const char* newName) override;
    int unlink(const char* path, int flags) override;
};

extern Reference<DevFS> devFS;

#endif
