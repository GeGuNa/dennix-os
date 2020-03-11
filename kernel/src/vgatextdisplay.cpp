/* Copyright (c) 2018, 2019, 2020 Dennis Wölfing
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

/* kernel/src/vgatextdisplay.cpp
 * VGA text mode display.
 */

#include <errno.h>
#include <string.h>
#include <dennix/display.h>
#include <dennix/kernel/portio.h>
#include <dennix/kernel/vgatextdisplay.h>

// In _start the video memory is mapped at this address.
static char* const video = (char*)
#ifdef __i386__
        0xC0000000
#elif defined(__x86_64__)
        0xFFFFFFFF80000000
#endif
;

static inline char* videoOffset(CharPos position) {
    return video + 2 * position.y * 80 + 2 * position.x;
}

VgaTextDisplay::VgaTextDisplay() {
    _height = 25;
    _width = 80;
}

void VgaTextDisplay::clear(CharPos from, CharPos to, Color color) {
    char* begin = videoOffset(from);
    char* end = videoOffset(to);

    while (begin <= end) {
        begin[0] = 0;
        begin[1] = color.vgaColor;
        begin += 2;
    }
}

void VgaTextDisplay::initialize() {
}

void VgaTextDisplay::putCharacter(CharPos position, wchar_t wc, Color color) {
    uint8_t vgaColor = color.vgaColor;
    uint8_t cp437 = unicodeToCp437(wc);
    if (cp437 == 0xFF) {
        // Print unrepresentable characters as ? with inverted colors.
        cp437 = '?';
        vgaColor = ((vgaColor & 0x0F) << 4) | ((vgaColor & 0xF0) >> 4);
    }

    *videoOffset(position) = cp437;
    *(videoOffset(position) + 1) = vgaColor;
}

void VgaTextDisplay::scroll(unsigned int lines, Color color,
        bool up /*= true*/) {
    size_t size = 2 * (height() - lines) * width();
    if (up) {
        memmove(video, videoOffset({0, lines}), size);
        clear({0, height() - lines}, {width() - 1, height() - 1}, color);
    } else {
        memmove(videoOffset({0, lines}), video, size);
        clear({0, 0}, {width() - 1, lines - 1}, color);
    }
}

void VgaTextDisplay::setCursorPos(CharPos position) {
    uint16_t value = position.x + position.y * 80;
    outb(0x3D4, 0x0E);
    outb(0x3D5, (value >> 8) & 0xFF);
    outb(0x3D4, 0x0F);
    outb(0x3D5, value & 0xFF);
}

void VgaTextDisplay::update() {

}

int VgaTextDisplay::devctl(int command, void* restrict data, size_t size,
        int* restrict info) {
    switch (command) {
    case DISPLAY_SET_MODE: {
        if (size != 0 && size != sizeof(int)) {
            *info = -1;
            return EINVAL;
        }

        const int* mode = (const int*) data;
        *info = DISPLAY_MODE_TEXT;

        if (*mode == DISPLAY_MODE_QUERY || *mode == DISPLAY_MODE_TEXT) {
            return 0;
        } else {
            return ENOTSUP;
        }
    } break;
    case DISPLAY_GET_RESOLUTION:
        *info = -1;
        if (size != 0 && size != sizeof(struct display_resolution)) {
            return EINVAL;
        }
        return ENOTSUP;
    case DISPLAY_DRAW:
        *info = -1;
        if (size != 0 && size != sizeof(struct display_draw)) {
            return EINVAL;
        }
        return ENOTSUP;
    default:
        *info = -1;
        return EINVAL;
    }
}

uint8_t unicodeToCp437(wchar_t wc) {
    // Translate Unicode characters into the code page 437 character set.
    // Note that some cp437 characters are used to represent multiple different
    // characters.
    if (wc == 0 || (wc >= 0x20 && wc <= 0x7E)) return wc;

    switch (wc) {
    case L'☺': return 0x01;
    case L'☻': return 0x02;
    case L'♥': return 0x03;
    case L'♦': return 0x04;
    case L'♣': return 0x05;
    case L'♠': return 0x06;
    case L'•': return 0x07;
    case L'◘': return 0x08;
    case L'○': return 0x09;
    case L'◙': return 0x0A;
    case L'♂': return 0x0B;
    case L'♀': return 0x0C;
    case L'♪': return 0x0D;
    case L'♫': return 0x0E;
    case L'☼': return 0x0F;
    case L'►': return 0x10;
    case L'◄': return 0x11;
    case L'↕': return 0x12;
    case L'‼': return 0x13;
    case L'¶': return 0x14;
    case L'§': return 0x15;
    case L'▬': return 0x16;
    case L'↨': return 0x17;
    case L'↑': return 0x18;
    case L'↓': return 0x19;
    case L'→': return 0x1A;
    case L'←': return 0x1B;
    case L'∟': return 0x1C;
    case L'↔': return 0x1D;
    case L'▲': return 0x1E;
    case L'▼': return 0x1F;
    case L'Δ': return 0x7F; // U+0394 GREEK CAPITAL LETTER DELTA
    case L'⌂': return 0x7F; // U+2302 HOUSE
    case L'Ç': return 0x80;
    case L'ü': return 0x81;
    case L'é': return 0x82;
    case L'â': return 0x83;
    case L'ä': return 0x84;
    case L'à': return 0x85;
    case L'å': return 0x86;
    case L'ç': return 0x87;
    case L'ê': return 0x88;
    case L'ë': return 0x89;
    case L'è': return 0x8A;
    case L'ï': return 0x8B;
    case L'î': return 0x8C;
    case L'ì': return 0x8D;
    case L'Ä': return 0x8E;
    case L'Å': return 0x8F;
    case L'É': return 0x90;
    case L'æ': return 0x91;
    case L'Æ': return 0x92;
    case L'ô': return 0x93;
    case L'ö': return 0x94;
    case L'ò': return 0x95;
    case L'û': return 0x96;
    case L'ù': return 0x97;
    case L'ÿ': return 0x98;
    case L'Ö': return 0x99;
    case L'Ü': return 0x9A;
    case L'¢': return 0x9B;
    case L'£': return 0x9C;
    case L'¥': return 0x9D;
    case L'₧': return 0x9E;
    case L'ƒ': return 0x9F;
    case L'á': return 0xA0;
    case L'í': return 0xA1;
    case L'ó': return 0xA2;
    case L'ú': return 0xA3;
    case L'ñ': return 0xA4;
    case L'Ñ': return 0xA5;
    case L'ª': return 0xA6;
    case L'º': return 0xA7;
    case L'¿': return 0xA8;
    case L'⌐': return 0xA9;
    case L'¬': return 0xAA;
    case L'½': return 0xAB;
    case L'¼': return 0xAC;
    case L'¡': return 0xAD;
    case L'«': return 0xAE;
    case L'»': return 0xAF;
    case L'░': return 0xB0;
    case L'▒': return 0xB1;
    case L'▓': return 0xB2;
    case L'│': return 0xB3;
    case L'┤': return 0xB4;
    case L'╡': return 0xB5;
    case L'╢': return 0xB6;
    case L'╖': return 0xB7;
    case L'╕': return 0xB8;
    case L'╣': return 0xB9;
    case L'║': return 0xBA;
    case L'╗': return 0xBB;
    case L'╝': return 0xBC;
    case L'╜': return 0xBD;
    case L'╛': return 0xBE;
    case L'┐': return 0xBF;
    case L'└': return 0xC0;
    case L'┴': return 0xC1;
    case L'┬': return 0xC2;
    case L'├': return 0xC3;
    case L'─': return 0xC4;
    case L'┼': return 0xC5;
    case L'╞': return 0xC6;
    case L'╟': return 0xC7;
    case L'╚': return 0xC8;
    case L'╔': return 0xC9;
    case L'╩': return 0xCA;
    case L'╦': return 0xCB;
    case L'╠': return 0xCC;
    case L'═': return 0xCD;
    case L'╬': return 0xCE;
    case L'╧': return 0xCF;
    case L'╨': return 0xD0;
    case L'╤': return 0xD1;
    case L'╥': return 0xD2;
    case L'╙': return 0xD3;
    case L'╘': return 0xD4;
    case L'╒': return 0xD5;
    case L'╓': return 0xD6;
    case L'╫': return 0xD7;
    case L'╪': return 0xD8;
    case L'┘': return 0xD9;
    case L'┌': return 0xDA;
    case L'█': return 0xDB;
    case L'▄': return 0xDC;
    case L'▌': return 0xDD;
    case L'▐': return 0xDE;
    case L'▀': return 0xDF;
    case L'α': return 0xE0;
    case L'ß': return 0xE1; // U+00DF LATIN SMALL LETTER SHARP S
    case L'β': return 0xE1; // U+03B2 GREEK SMALL LETTER BETA
    case L'Γ': return 0xE2;
    case L'π': return 0xE3;
    case L'Σ': return 0xE4; // U+03A3 GREEK CAPITAL LETTER SIGMA
    case L'∑': return 0xE4; // U+2211 N-ARY SUMMATION
    case L'σ': return 0xE5;
    case L'µ': return 0xE6; // U+00B5 MICRO SIGN
    case L'μ': return 0xE6; // U+03BC GREEK SMALL LETTER MU
    case L'τ': return 0xE7;
    case L'Φ': return 0xE8;
    case L'Θ': return 0xE9;
    case L'Ω': return 0xEA; // U+03A9 GREEK CAPITAL LETTER OMEGA
    case L'Ω': return 0xEA; // U+2126 OHM SIGN
    case L'ð': return 0xEB; // U+00F0 LATIN SMALL LETTER ETH
    case L'δ': return 0xEB; // U+03B4 GREEK SMALL LETTER DELTA
    case L'∂': return 0xEB; // U+2202 PARTIAL DIFFERENTIAL
    case L'∞': return 0xEC;
    case L'Ø': return 0xED; // U+00D8 LATIN CAPITAL LETTER O WITH STROKE
    case L'ø': return 0xED; // U+00F8 LATIN SMALL LETTER O WITH STROKE
    case L'φ': return 0xED; // U+03C6 GREEK SMALL LETTER PHI
    case L'ϕ': return 0xED; // U+03D5 GREEK PHI SYMBOL
    case L'∅': return 0xED; // U+2205 EMPTY SET
    case L'⌀': return 0xED; // U+2300 DIAMETER SIGN
    case L'𝜙': return 0xED; // U+1D719 MATHEMATICAL ITALIC PHI SYMBOL
    case L'ε': return 0xEE; // U+03B5 GREEK SMALL LETTER EPSILON
    case L'€': return 0xEE; // U+20AC EURO SIGN
    case L'∈': return 0xEE; // U+2208 ELEMENT OF
    case L'∩': return 0xEF;
    case L'≡': return 0xF0;
    case L'±': return 0xF1;
    case L'≥': return 0xF2;
    case L'≤': return 0xF3;
    case L'⌠': return 0xF4;
    case L'⌡': return 0xF5;
    case L'÷': return 0xF6;
    case L'≈': return 0xF7;
    case L'°': return 0xF8;
    case L'∙': return 0xF9;
    case L'·': return 0xFA;
    case L'√': return 0xFB;
    case L'ⁿ': return 0xFC;
    case L'²': return 0xFD;
    case L'■': return 0xFE;

    // Use 0xFF for characters that cannot be represented by cp437.
    default: return 0xFF;
    }
}
