#pragma once
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_FRE   (80000000)
#define LCD_BIT   (1)
#define LCD_WIDTH (320)
#define LCD_HIGH  (240)

#define LCD_CLK   (GPIO_NUM_4)
#define LCD_MOSI  (GPIO_NUM_5)
#define LCD_DC    (GPIO_NUM_6)
#define LCD_RD    (-1)
#define LCD_RST   (GPIO_NUM_7)
#define LCD_CS    (GPIO_NUM_8)
#define LCD_BK    (GPIO_NUM_9)

#ifdef __cplusplus
}
#endif