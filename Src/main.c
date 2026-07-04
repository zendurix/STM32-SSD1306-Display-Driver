#include <stdint.h>
#include <stdbool.h>

#include "stm32u031xx.h"

#include "LD_4.h"
#include "USER_button.h"
#include "clock.h"
#include "Display/display.h"

/*
 SSD1306 128x32 OLED example usage:
 Board used - Nucleo STM32U031R8T6.
 Connections:
 OLED VCC -> Board 3V3
 OLED GND -> Board GND
 OLED SDA -> Board D14 (PB9 on processor)
 OLED SCL -> Board D15 (PB8 on processor)

 This programs shows 3 modes of my own SSD1306 128x32 driver:
 0 - Clock Mode - Display shows current time in HH:MM format. start time for now is hard coded 00::00,
 .	but can be later setup with additional buttons.

 1 - Text Mode - Display shows text in 8x8 font. Screen is divided into 16x4 tiles for letters (spacing == 0)
 .	text can be written on screen as single characters with xy pos (where xy is letter tile pos x:0-15, y:0-3)
 .	or as strings with starting pos xy, strings are written char by char into next tiles, and wrap to next line

 2 - Image Mode - Display shows 128x32 black and white images, that are stored on device flash memory. Images are stored
 .	as uint8_t[512] bitmaps representing whole buffer of oled screen.
 .	Images can be converted to this format with "\python_scripts\image_converter.py"

 Pressing USER button (on board):
 - short press (<1s) - toggle display ON/OFF, switch to next image in images mode
 - long press (>1s) - switch to next Mode (0 -> 1 -> 2 -> 0 -> 1 ...)

 */

#define TOGGLE_PROGRAM_MODE_PRESS_TIME 1000

int main(void) {
	CLOCK_configure();

	// 16Mhz base, 1ms interrupts
	SysTick_Config(16000000 / 1000);

	// fast clock test
	//SysTick_Config(16000000 / 300000);

	LD4_configure();
	USER_button_configure();

	Display *display = Display_create(20, 12, 42, G_Tick);
	if (!display) {
		return 1;
	}

	Display_set_hour_minute(display, 20, 37);
	Display_add_string_to_text(display, "test msg 1", 0, 0);
	Display_add_string_to_text(display, "test msg 2", 0, 1);
	Display_add_string_to_text(display, "test msg 3", 0, 2);
	Display_add_string_to_text(display, "test msg 4", 0, 3);
	Display_add_string_to_text(display, "@", 15, 3);

	while (true) {
		USER_button_update();

		if (G_USER_button_state == ButtonState_RELEASED) {
			if (G_USER_button_time_pressed_ms > TOGGLE_PROGRAM_MODE_PRESS_TIME) {
				Display_switch_to_next_mode(display);
			} else {
				if (Display_get_mode(display) == DisplayMode_IMAGE) {
					Display_switch_to_next_image(display);
				} else {
					Display_toggle_on_off(display);
				}
			}
		}

		Display_update(display, G_Tick);
	}
}
