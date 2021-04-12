#pragma once
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_FRE   (80000000)
#define LCD_BIT   (1)
#define LCD_WIDTH (240)
#define LCD_HIGH  (240)

#define CAM_FRE   (5000000)
#define CAM_BIT   (8)
#define CAM_WIDTH (240)
#define CAM_HIGH  (240)

#define LCD_CLK   (GPIO_NUM_12)
#define LCD_MOSI  (GPIO_NUM_22)
#define LCD_DC    (GPIO_NUM_2)
#define LCD_RD    (-1)
#define LCD_RST   (GPIO_NUM_26)
#define LCD_CS    (GPIO_NUM_15)
#define LCD_BK    (-1)

#define CAM_XCLK  (GPIO_NUM_4)
#define CAM_PCLK  (GPIO_NUM_25)
#define CAM_VSYNC (GPIO_NUM_5)
#define CAM_HREF  (GPIO_NUM_27)

#define CAM_D0    (GPIO_NUM_34)
#define CAM_D1    (GPIO_NUM_13)
#define CAM_D2    (GPIO_NUM_14)
#define CAM_D3    (GPIO_NUM_35)
#define CAM_D4    (GPIO_NUM_39)
#define CAM_D5    (GPIO_NUM_21)
#define CAM_D6    (GPIO_NUM_19)
#define CAM_D7    (GPIO_NUM_36)

#define CAM_SCL   (GPIO_NUM_23)
#define CAM_SDA   (GPIO_NUM_18)

#define CAM_PWD   (GPIO_NUM_32)
#define CAM_RST   (GPIO_NUM_33)

#ifdef __cplusplus
}
#endif