#ifndef SSD1306_IMAGES_MODE_H
#define SSD1306_IMAGES_MODE_H

#include <stdint.h>
#include <stdbool.h>

#include "ssd1306.h"
#include "images.h"


extern uint8_t G_image_index;

void next_image(Display *display);

void draw_image(Display *display);

#endif /* SSD1306_IMAGES_MODE_H */
