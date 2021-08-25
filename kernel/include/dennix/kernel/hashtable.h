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

/* kernel/include/dennix/kernel/hashtable.h
 * Hash table.
 */

#ifndef KERNEL_HASHTABLE_H
#define KERNEL_HASHTABLE_H

#include <string.h>
#include <dennix/kernel/kernel.h>

// The type T must have a function hashKey() returning a unique TKey. It also
// needs to have a member T* nextInHashTable that is managed by the hash table.
// An object can only be member of one hash table at a time. That way we can
// implement the hash table in a way that operations cannot fail.
template <typename T, typename TKey = size_t>
class HashTable {
public:
    HashTable(size_t capacity, T* buffer[]) {
        table = buffer;
        memset(table, 0, capacity * sizeof(T*));
        this->capacity = capacity;
    }

    void add(T* object) {
        size_t hash = object->hashKey() % capacity;
        object->nextInHashTable = table[hash];
        table[hash] = object;
    }

    T* get(TKey key) {
        size_t hash = key % capacity;

        T* obj = table[hash];
        while (obj) {
            if (obj->hashKey() == key) {
                return obj;
            }
            obj = obj->nextInHashTable;
        }

        return nullptr;
    }

    void remove(TKey key) {
        size_t hash = key % capacity;

        T* obj = table[hash];
        if (obj->hashKey() == key) {
            table[hash] = obj->nextInHashTable;
            return;
        }
        while (obj->nextInHashTable) {
            T* next = obj->nextInHashTable;
            if (next->hashKey() == key) {
                obj->nextInHashTable = next->nextInHashTable;
                return;
            }
            obj = next;
        }
    }
private:
    T** table;
    size_t capacity;
};

#endif
