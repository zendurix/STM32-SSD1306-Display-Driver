#ifndef SSD1306_CLOCK_MODE_H
#define SSD1306_CLOCK_MODE_H

#include <stdint.h>
#include <stdbool.h>

#include "ssd1306.h"

typedef enum EDigitPos {
	DigitPos_HH_0 = 0, //
	DigitPos_HH_1, //
	DigitPos_MM_0, //
	DigitPos_MM_1, //
} EDigitPos;

typedef struct ClockHHMM {
	uint8_t hour;
	uint8_t minute;

	uint32_t last_minute_time_stamp;
	bool is_dirty;

} ClockHHMM;

void ClockHHMM_init(ClockHHMM *clock, uint8_t hour, uint8_t minute,
		uint32_t milliseconds);
void ClockHHMM_update(ClockHHMM *clock, uint32_t milliseconds);
void ClockHHMM_update_display(ClockHHMM *clock, Display *display);

void add_to_buffer_colon(Display *display);

void add_to_buffer_digit(Display *display, int8_t digit, EDigitPos digit_pos);

void add_to_buffer_digit_pixels(Display *display, uint8_t pixels[][2],
		uint16_t pixels_num, EDigitPos digit_pos);

void add_to_buffer_digit_0(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_1(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_2(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_3(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_4(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_5(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_6(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_7(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_8(Display *display, EDigitPos digit_pos);
void add_to_buffer_digit_9(Display *display, EDigitPos digit_pos);

#endif /* SSD1306_CLOCK_MODE_H*/
