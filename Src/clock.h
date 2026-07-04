#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32u031xx.h"

// increases by 1 every millisecond
extern volatile uint32_t G_Tick;

// configures system clock to HSI16 - 16MHz
void CLOCK_configure(void);

void SysTick_Handler(void);

void Delay(uint32_t delay_ms);

#endif /* CLOCK_H */
