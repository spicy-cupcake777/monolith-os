#pragma once

#include "colors.h"

typedef char color_t;	// fg | bg << 4
typedef short vchar_t;	// ch | cl << 8
const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;
vchar_t* VGA_BUFFER = (vchar_t*) 0x0b8000;

struct term_t {
	short x; short y;
	color_t color;
};


static struct term_t TERM = (struct term_t) { x: 0, y: 0, color: 0x0b };

// DO NOT use this for typical use; for organization's sake there will be a similar
// implementation of this in a string.h header
int _v_strlen(const char* s) {
	int i = 0;
	while (s[i++]) ;
	return i;
}

// alters the static TERM's color attribute
void set_color(char fg, char bg) {
	TERM.color = fg | bg << 4;
}
// constructs a vchar_t using a regular char and a color_t color
vchar_t get_char(char c, color_t l) {
	return (vchar_t) c | l << 8;
}
// put a single character to the VGA buffer
// TODO handle special characters such as newlines or carriage returns
void v_putc(char c) {
	switch (c) {
		case ' ' ... '~':
			VGA_BUFFER[TERM.x + (TERM.y * VGA_WIDTH)] = get_char(c, TERM.color);
			if ((TERM.x++) > VGA_WIDTH) {
				TERM.x = 0;
				if ((TERM.y++) > VGA_HEIGHT) TERM.y = 0;
			}
			break;
		case '\n':
			TERM.x = 0;
			if ((TERM.y++) > VGA_HEIGHT) TERM.y = 0;
			break;
	}
}
// put a string of specified length to buffer
void v_puts(const char* m, const int l) {
	for (int i = 0; i < l; ++i) {
		v_putc(m[i]);
	}
}
// put a string to buffer, automatically determine length
void v_print(const char* m) {
	v_puts(m, _v_strlen(m));
}
// put a string to the buffer link v_print, but also add a newline
void v_println(const char* m) {
	v_print(m);
	v_putc('\n');
}
