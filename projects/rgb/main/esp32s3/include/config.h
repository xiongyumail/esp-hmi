#pragma once
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_FRE   (18500000)
#define LCD_BIT   (16)
#define LCD_WIDTH (800)
#define LCD_HIGH  (480)

#define LCD_PCLK  (GPIO_NUM_21)
#define LCD_VSYNC (GPIO_NUM_48)
#define LCD_HSYNC (GPIO_NUM_47)
#define LCD_HREF  (GPIO_NUM_45)

#define LCD_D0    (GPIO_NUM_3)
#define LCD_D1    (GPIO_NUM_4)
#define LCD_D2    (GPIO_NUM_5)
#define LCD_D3    (GPIO_NUM_6)
#define LCD_D4    (GPIO_NUM_7)
#define LCD_D5    (GPIO_NUM_8)
#define LCD_D6    (GPIO_NUM_9)
#define LCD_D7    (GPIO_NUM_10)
#define LCD_D8    (GPIO_NUM_11)
#define LCD_D9    (GPIO_NUM_12)
#define LCD_D10   (GPIO_NUM_13)
#define LCD_D11   (GPIO_NUM_14)
#define LCD_D12   (GPIO_NUM_15)
#define LCD_D13   (GPIO_NUM_16)
#define LCD_D14   (GPIO_NUM_17)
#define LCD_D15   (GPIO_NUM_18)

#define I2C_SCL   (GPIO_NUM_1)
#define I2C_SDA   (GPIO_NUM_2)

#define CAM_PWD   (-1)
#define CAM_RST   (-1)

#ifdef __cplusplus
}
#endif