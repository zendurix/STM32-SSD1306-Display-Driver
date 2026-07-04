#include "images_mode.h"

// memcpy
#include <string.h>

uint8_t G_image_index = 0;

void next_image(Display *display) {
	if (!display) {
		return;
	}

	G_image_index++;
	if (G_image_index >= IMAGES_COUNT) {
		G_image_index = 0;
	}

	draw_image(display);
}

void draw_image(Display *display) {
	if (!display) {
		return;
	}

	Display_clear_buffer(display);

	for (uint16_t page_num = 0; page_num < SSD1306_PAGES_NUM; page_num++) {
		memcpy(display->pages[page_num].buffer,
				&images[G_image_index][page_num * SSD1306_PAGE_SIZE],
				SSD1306_PAGE_SIZE);
		display->pages[page_num].is_dirty = true;
		display->pages[page_num].is_empty = false;
	}

	Display_draw_buffer(display);
}
