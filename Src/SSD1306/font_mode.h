#ifndef SSD1306_FONT_MODE_H
#define SSD1306_FONT_MODE_H

#include <stdint.h>
#include <stdbool.h>

#include "ssd1306.h"

// Alignment:2 pixel in y, 1 pixel in x
// char_x: <0-15>
// char_y: <0-3>
// max 64 characters on screen

#define CHAR_PIXEL_SIZE 8
#define TEXT_COLS 16
#define TEXT_ROWS 4

typedef struct FontMode {
	char text[TEXT_ROWS][TEXT_COLS];

	bool is_dirty;

} FontMode;

void FontMode_init(FontMode *font_mode);

void FontMode_clear_text(FontMode *font_mode);

void FontMode_add_char_to_text(FontMode *font_mode, uint8_t character,
		uint8_t char_x, uint8_t char_y);

void FontMode_add_string_to_text(FontMode *font_mode, const char *msg,
		uint8_t start_x, uint8_t start_y);

void FontMode_draw_text(FontMode *font_mode, Display *display);

void add_char_to_buffer(Display *display, uint8_t character, uint8_t char_x,
		uint8_t char_y);

#endif /* SSD1306_FONT_MODE_H */
