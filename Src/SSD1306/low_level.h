#ifndef SSD1306_LOW_LEVEL_H
#define SSD1306_LOW_LEVEL_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32u031xx.h"

// SDA -> PB9 (D14)
// SCL -> PB8 (D15)

/*
 Low level operations on NUCLEO board STM32U031R8T6 to connect with OLED display 128x32 SSD1306 using I2C protocol.

 Connecting OLED (left - OLED pin <-> Nucleo Pin (Processor pin)) :
 * VCC <-> 3V3
 * GND <-> GND
 * SCK/SCL <-> D15 (PB8)
 * SDA <-> D14 (PB9)


 */


#define SSD1306_CONTROLL_BYTE_COMMAND_MODE 0b00000000
#define SSD1306_CONTROLL_BYTE_DATA_MODE 0b01000000
// Display is split into horizontal pages, each consisting of 128 bytes - 128x8 pixels.
#define SSD1306_PAGES_NUM 4U
#define SSD1306_PAGE_SIZE 128U
#define BYTE_BUFFER_SIZE 512U

void ssd1306_configure_pins();

void ssd1306_configure_i2c();

void ssd1306_init_transfer(uint8_t bytes_num);

void ssd1306_wait_for_previous_transfer_end();

void ssd1306_send_byte(uint8_t byte);

#endif /* SSD1306_LOW_LEVEL_H */
