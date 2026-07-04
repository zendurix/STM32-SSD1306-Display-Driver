#include "ssd1306.h"

#include "../clock.h"
#include "images.h"

void Display_initialize(Display *display) {
	if (!display) {
		return;
	}

	for (uint8_t page_num = 0; page_num < SSD1306_PAGES_NUM; page_num++) {
		display->pages[page_num].page_num = page_num;
		display->pages[page_num].is_empty = false;
		display->pages[page_num].is_dirty = true;
	}

	Delay(500);
	ssd1306_configure_pins();
	ssd1306_configure_i2c();
	Display_send_initialization_data();

	Display_clear_buffer(display);
}

void Display_send_initialization_data() {
#define INIT_DATA_SIZE 24
	ssd1306_init_transfer(INIT_DATA_SIZE);
	uint8_t initialization_data_transfer[INIT_DATA_SIZE] = { // newline
			// newline
					SSD1306_CONTROLL_BYTE_COMMAND_MODE,// CONTROL byte

					0xA8, 31, // COMMAND set Multiplexer ratio (31 for 128x32 display)

					0xD3, 0,  // COMMAND set display offset, 0 - no offset

					0x40, // set display start line - 0

					0xA1, // set segment re-map

					0xC8, // set COM output scan direction

					0xDA, 0x02, // set COM pins hardware configuration

					0x81, 15, // set contrast control (0-255)

					0xA4, // set entire display ON - A5, Off (display from RAM - A4)  ////////////////////////////

					0xA6, // set normal display

					0xD5, 0b10000000, // set display clock divide ratio / oscillator frequency, (RESET value)

					0x20, 0x02, // set memory addressing mode 2 - page addressing mode

					0x8D, 0x14, // Enable charge pump regulator

					0xAF, // DISPLAY ON !!!
			};

	for (uint8_t i = 0; i < INIT_DATA_SIZE; i++) {
		ssd1306_send_byte(initialization_data_transfer[i]);
	}
}

void Display_draw_buffer(Display *display) {
	if (!display) {
		return;
	}

	for (uint8_t page_num = 0; page_num < SSD1306_PAGES_NUM; page_num++) {
		if (!display->pages[page_num].is_dirty) {
			continue;
		}

		ssd1306_wait_for_previous_transfer_end();
		switch_display_page_writing(page_num);
		ssd1306_wait_for_previous_transfer_end();

		Display_draw_page(&display->pages[page_num]);
		display->pages[page_num].is_dirty = false;
	}
}

void Display_draw_page(DisplayPage *page) {
	if (!page) {
		return;
	}

	ssd1306_init_transfer(SSD1306_PAGE_SIZE + 1);
	ssd1306_send_byte(SSD1306_CONTROLL_BYTE_DATA_MODE);

	for (uint16_t i = 0; i < SSD1306_PAGE_SIZE; i++) {
		ssd1306_send_byte(page->buffer[i]);
	}
}

void switch_display_page_writing(uint8_t page_num) {
#define SWITCH_DATA_SIZE 4
	ssd1306_init_transfer(SWITCH_DATA_SIZE);
	uint8_t switch_page_data_transfer[SWITCH_DATA_SIZE] = { // newline
			// newline
					SSD1306_CONTROLL_BYTE_COMMAND_MODE,//
					0xB0 + page_num, // COMMAND Setup page start
					0x00, // COMMAND column address lower part  [3:0]
					0x10, // COMMAND column address higher part [7:4]
			};

	for (uint8_t i = 0; i < SWITCH_DATA_SIZE; i++) {
		ssd1306_send_byte(switch_page_data_transfer[i]);
	}
}

void Display_clear_buffer(Display *display) {
	if (!display)
		return;

	for (uint8_t page_num = 0; page_num < SSD1306_PAGES_NUM; page_num++) {
		if (display->pages[page_num].is_empty) {
			continue;
		}

		for (uint16_t i = 0; i < SSD1306_PAGE_SIZE; i++) {
			display->pages[page_num].buffer[i] = 0;
		}
		display->pages[page_num].is_empty = true;
		display->pages[page_num].is_dirty = true;
	}
}

void Display_set_pixel(Display *display, uint8_t x, uint8_t y, bool pixel_on) {
	if (!display || x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT)
		return;

	const uint8_t page_num = y / 8;
	const uint8_t byte_bit = y % 8;

	uint8_t *byte = &display->pages[page_num].buffer[x];

	if (pixel_on) {
		display->pages[page_num].is_empty = false;
		*byte |= (1 << byte_bit);
	} else {
		*byte &= ~(1 << byte_bit);
	}

	display->pages[page_num].is_dirty = true;
}

void toggle_display_on_off() {
	static bool is_ON = true;

	is_ON = !is_ON;

	ssd1306_init_transfer(2);

	ssd1306_send_byte(SSD1306_CONTROLL_BYTE_COMMAND_MODE);

	if (is_ON) {
		ssd1306_send_byte(0xAF);
	} else {

		ssd1306_send_byte(0xAE);
	}

	while (!(I2C1->ISR & I2C_ISR_STOPF))
		;
	I2C1->ICR = I2C_ICR_STOPCF;
}
