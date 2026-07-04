#include <stdint.h>
#include <stdbool.h>

#include "stm32u031xx.h"

#include "LD_4.h"
#include "USER_button.h"
#include "clock.h"
#include "SSD1306/ssd1306.h"
#include "SSD1306/clock_mode.h"
#include "SSD1306/font_mode.h"
#include "SSD1306/images_mode.h"

// optional Flash memory usage to store and restore LD4 state and program state
// #define USE_FLASH
#ifdef USE_FLASH
#include "flash_mem.h"
static FlashMemPage flash_page;
#endif // USE_FLASH

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



 optional Flash memory usage (uncomment // #define USE_FLASH above) - store LD4 and Program states between restarts.
 */

typedef enum EProgramState {
	ProgramState_Clock = 0, //
	ProgramState_Text, //
	ProgramState_Images,
} EProgramState;

EProgramState G_Program_state = ProgramState_Clock;

#define TOGGLE_PROGRAM_MODE_PRESS_TIME 1000
#define SHORT_PRESS_TIME 500
#define BLINK_STEP 100
#define BLINK_DEFAULT 1000

int main(void) {
	CLOCK_configure();

	// 16Mhz base, 1ms interrupts
	//SysTick_Config(16000000 / 1000);

	// fast clock test
	SysTick_Config(16000000 / 300000);


	LD4_configure();
	USER_button_configure();

	ClockHHMM clock_hh_mm;
	ClockHHMM_init(&clock_hh_mm, 00, 00, G_Tick);

	FontMode font_mode;
	FontMode_init(&font_mode);
	char *msg1 = "Temp(A): 21,37C";
	FontMode_add_string_to_text(&font_mode, msg1, 0, 0);
	char *msg2 = "Temp(D): 21,22C";
	FontMode_add_string_to_text(&font_mode, msg2, 0, 1);
	char *msg3 = "mean: 20,10C";
	FontMode_add_string_to_text(&font_mode, msg3, 0, 2);

	Display display;
	Display_initialize(&display);

	bool set = false;


	while (true) {
		USER_button_update();
		ClockHHMM_update(&clock_hh_mm, G_Tick);

		for (int i = 0; i < 1000; i ++)
		{



		}


		if (G_USER_button_state == ButtonState_RELEASED) {
			if (G_USER_button_time_pressed_ms > TOGGLE_PROGRAM_MODE_PRESS_TIME) {
				G_Program_state++;
				if (G_Program_state > 2) {
					G_Program_state = 0;
				}

				clock_hh_mm.is_dirty = true;
				font_mode.is_dirty = true;
				set = false;
			} else {
				if (G_Program_state == ProgramState_Images) {
					next_image(&display);
				} else {
					toggle_display_on_off();
				}
			}
		}

		////////////////////////////////////////////////////////

		switch (G_Program_state) {
		case ProgramState_Clock: {
			ClockHHMM_update_display(&clock_hh_mm, &display);
			break;
		}
		case ProgramState_Text: {
			FontMode_draw_text(&font_mode, &display);
			break;
		}

		case ProgramState_Images: {
			if (!set) {
				draw_image(&display);
				set = true;
			}
		}
		} // switch end

	}
}
