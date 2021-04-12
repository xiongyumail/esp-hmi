#pragma once
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_FRE   (80000000)
#define LCD_BIT   (1)
#define LCD_WIDTH (240)
#define LCD_HIGH  (320)

#define CAM_FRE   (16000000)
#define CAM_BIT   (8)
#define CAM_WIDTH (240)
#define CAM_HIGH  (320)

#define LCD_CLK   (GPIO_NUM_6)
#define LCD_MOSI  (GPIO_NUM_7)
#define LCD_DC    (GPIO_NUM_8)
#define LCD_RD    (-1)
#define LCD_RST   (GPIO_NUM_9)
#define LCD_CS    (GPIO_NUM_10)
#define LCD_BK    (GPIO_NUM_11)

#define CAM_XCLK  (GPIO_NUM_42)
#define CAM_PCLK  (GPIO_NUM_3)
#define CAM_VSYNC (GPIO_NUM_38)
#define CAM_HREF  (GPIO_NUM_4)

#define CAM_D0    (GPIO_NUM_14)
#define CAM_D1    (GPIO_NUM_12)
#define CAM_D2    (GPIO_NUM_5)
#define CAM_D3    (GPIO_NUM_13)
#define CAM_D4    (GPIO_NUM_15)
#define CAM_D5    (GPIO_NUM_40)
#define CAM_D6    (GPIO_NUM_39)
#define CAM_D7    (GPIO_NUM_16)

#define CAM_SCL   (GPIO_NUM_18)
#define CAM_SDA   (GPIO_NUM_41)

#define CAM_PWD   (GPIO_NUM_1)
#define CAM_RST   (GPIO_NUM_2)

#ifdef __cplusplus
}
#endif