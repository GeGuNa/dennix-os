/* Copyright (c) 2016, Dennis Wölfing
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

/* kernel/src/idt.cpp
 * Defines the IDT.
 */

#include <stdint.h>
#include <dennix/kernel/kernel.h>

extern "C" {
// CPU Exceptions
extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_19(void);
extern void isr_20(void);

// IRQs
extern void isr_32(void);
extern void isr_33(void);
extern void isr_34(void);
extern void isr_35(void);
extern void isr_36(void);
extern void isr_37(void);
extern void isr_38(void);
extern void isr_39(void);
extern void isr_40(void);
extern void isr_41(void);
extern void isr_42(void);
extern void isr_43(void);
extern void isr_44(void);
extern void isr_45(void);
extern void isr_46(void);
extern void isr_47(void);

}

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t unused;
    uint8_t flags;
    uint16_t offset_high;
};

#define IDT_ENTRY(offset, selector, flags) { \
    (uint16_t)((uintptr_t)(offset) & 0xFFFF), \
    (selector), \
    0, \
    (flags), \
    (uint16_t)(((uintptr_t)(offset) >> 16) & 0xFFFF) \
}

#define IDT_INTERRUPT_GATE 0xE
#define IDT_RING0 0
#define IDT_PRESENT (1 << 7)

idt_entry idt[] = {
    /*[0] =*/ IDT_ENTRY(isr_0, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[1] =*/ IDT_ENTRY(isr_1, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[2] =*/ IDT_ENTRY(isr_2, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[3] =*/ IDT_ENTRY(isr_3, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[4] =*/ IDT_ENTRY(isr_4, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[5] =*/ IDT_ENTRY(isr_5, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[6] =*/ IDT_ENTRY(isr_6, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[7] =*/ IDT_ENTRY(isr_7, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[8] =*/ IDT_ENTRY(isr_8, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[9] =*/ IDT_ENTRY(isr_9, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[10] =*/ IDT_ENTRY(isr_10, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[11] =*/ IDT_ENTRY(isr_11, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[12] =*/ IDT_ENTRY(isr_12, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[13] =*/ IDT_ENTRY(isr_13, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[14] =*/ IDT_ENTRY(isr_14, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[15] =*/ IDT_ENTRY(0, 0, 0),
    /*[16] =*/ IDT_ENTRY(isr_16, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[17] =*/ IDT_ENTRY(isr_17, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[18] =*/ IDT_ENTRY(isr_18, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[19] =*/ IDT_ENTRY(isr_19, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[20] =*/ IDT_ENTRY(isr_20, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),

    /*[21] =*/ IDT_ENTRY(0, 0, 0),
    /*[22] =*/ IDT_ENTRY(0, 0, 0),
    /*[23] =*/ IDT_ENTRY(0, 0, 0),
    /*[24] =*/ IDT_ENTRY(0, 0, 0),
    /*[25] =*/ IDT_ENTRY(0, 0, 0),
    /*[26] =*/ IDT_ENTRY(0, 0, 0),
    /*[27] =*/ IDT_ENTRY(0, 0, 0),
    /*[28] =*/ IDT_ENTRY(0, 0, 0),
    /*[29] =*/ IDT_ENTRY(0, 0, 0),
    /*[30] =*/ IDT_ENTRY(0, 0, 0),
    /*[31] =*/ IDT_ENTRY(0, 0, 0),

    /*[32] =*/ IDT_ENTRY(isr_32, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[33] =*/ IDT_ENTRY(isr_33, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[34] =*/ IDT_ENTRY(isr_34, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[35] =*/ IDT_ENTRY(isr_35, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[36] =*/ IDT_ENTRY(isr_36, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[37] =*/ IDT_ENTRY(isr_37, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[38] =*/ IDT_ENTRY(isr_38, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[39] =*/ IDT_ENTRY(isr_39, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[40] =*/ IDT_ENTRY(isr_40, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[41] =*/ IDT_ENTRY(isr_41, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[42] =*/ IDT_ENTRY(isr_42, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[43] =*/ IDT_ENTRY(isr_43, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[44] =*/ IDT_ENTRY(isr_44, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[45] =*/ IDT_ENTRY(isr_45, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[46] =*/ IDT_ENTRY(isr_46, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
    /*[47] =*/ IDT_ENTRY(isr_47, 0x8, IDT_INTERRUPT_GATE | IDT_RING0 | IDT_PRESENT),
};

extern "C" {
struct {
    uint16_t size;
    void* idtp;
} PACKED idt_descriptor = {
    sizeof(idt) - 1,
    idt
};
}