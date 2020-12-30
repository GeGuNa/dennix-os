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

/* gui/guimsg.h
 * GUI messages.
 */

#ifndef GUIMSG_H
#define GUIMSG_H

#include <stddef.h>
#include <stdint.h>

enum {
    GUI_MSG_CLOSE_WINDOW,
    GUI_MSG_CREATE_WINDOW,
    GUI_MSG_HIDE_WINDOW,
    GUI_MSG_REDRAW_WINDOW,
    GUI_MSG_REDRAW_WINDOW_PART,
    GUI_MSG_SHOW_WINDOW,

    GUI_EVENT_STATUS = 10000,
    GUI_EVENT_CLOSE_BUTTON,
    GUI_EVENT_KEY,
    GUI_EVENT_MOUSE,
    GUI_EVENT_WINDOW_CREATED,
    GUI_EVENT_WINDOW_RESIZED,
};

struct gui_msg_header {
    unsigned int type;
    unsigned int length;
};

enum {
    GUI_WINDOW_NO_RESIZE = 1 << 0,
};

struct gui_msg_create_window {
    int x;
    int y;
    unsigned int width;
    unsigned int height;
    unsigned int flags;
    char title[];
};

struct gui_msg_close_window {
    unsigned int window_id;
};

struct gui_msg_hide_window {
    unsigned int window_id;
};

struct gui_msg_redraw_window {
    unsigned int window_id;
    unsigned int width;
    unsigned int height;
    uint32_t lfb[];
};

struct gui_msg_redraw_window_part {
    unsigned int window_id;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    unsigned int pitch;
    uint32_t lfb[];
};

struct gui_msg_show_window {
    unsigned int window_id;
};

struct gui_event_status {
    /* currently no flags are defined. */
    unsigned int flags;
    unsigned int display_width;
    unsigned int display_height;
};

struct gui_event_key {
    unsigned int window_id;
    int key;
    wchar_t codepoint;
};

enum {
    GUI_MOUSE_LEFT = 1 << 0,
    GUI_MOUSE_RIGHT = 1 << 1,
    GUI_MOUSE_MIDDLE = 1 << 2,
    GUI_MOUSE_SCROLL_UP = 1 << 3,
    GUI_MOUSE_SCROLL_DOWN = 1 << 4,
    GUI_MOUSE_LEAVE = 1 << 5,
};

struct gui_event_mouse {
    unsigned int window_id;
    unsigned int x;
    unsigned int y;
    unsigned int flags;
};

struct gui_event_window_created {
    unsigned int window_id;
};

struct gui_event_window_close_button {
    unsigned int window_id;
};

struct gui_event_window_resized {
    unsigned int window_id;
    unsigned int width;
    unsigned int height;
};

#endif
