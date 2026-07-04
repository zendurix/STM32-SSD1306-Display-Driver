#ifndef SSD1306_SSD1306_H
#define SSD1306_SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#include "low_level.h"

#define DISPLAY_WIDTH 128U
#define DISPLAY_HEIGHT 32U

typedef struct DisplayPage {
	uint8_t page_num;
	uint8_t buffer[SSD1306_PAGE_SIZE];

	bool is_dirty;
	bool is_empty;
} DisplayPage;

typedef struct Display {
	// Buffer containing all 128x32 pixels as bits. Data is drawn byte after byte, where one bite represents
	// 8 pixel column (starts from top left of screen).

	DisplayPage pages[SSD1306_PAGES_NUM];

} Display;

void Display_initialize(Display *display);

void Display_send_initialization_data();

void Display_draw_buffer(Display *display);

void Display_draw_page(DisplayPage *page);

void switch_display_page_writing(uint8_t page_num);

void Display_clear_buffer(Display *display);

void Display_set_pixel(Display *display, uint8_t x, uint8_t y, bool pixel_on);

void toggle_display_on_off();

#endif /* SSD1306_SSD1306_H */
