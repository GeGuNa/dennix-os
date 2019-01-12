# Copyright (c) 2016, 2019 Dennis Wölfing
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

include x86-family.mk

CRTI_O = $(shell $(CXX) $(CXXFLAGS) -print-file-name=crti.o)
CRTBEGIN_O = $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND_O = $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTN_O = $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtn.o)

START_OBJ = $(CRTI_O) $(CRTBEGIN_O)
END_OBJ = $(CRTEND_O) $(CRTN_O)

OBJ += \
	arch/i686/addressspace.o \
	arch/i686/interrupts.o \
	arch/i686/registers.o \
	arch/i686/start.o \
	arch/i686/syscall.o
