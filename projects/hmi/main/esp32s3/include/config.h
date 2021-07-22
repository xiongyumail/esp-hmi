#pragma once
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_FRE   (20000000)
#define LCD_BIT   (8)
#define LCD_WIDTH (320)
#define LCD_HIGH  (480)

#define CAM_FRE   (16000000)
#define CAM_BIT   (8)
#define CAM_WIDTH (480)
#define CAM_HIGH  (320)

#define LCD_WR    (GPIO_NUM_4)
#define LCD_DC    (GPIO_NUM_2)
#define LCD_RD    (-1)
#define LCD_RST   (-1)
#define LCD_CS    (-1)
#define LCD_BK    (-1)

#define LCD_D0    (GPIO_NUM_45)
#define LCD_D1    (GPIO_NUM_16)
#define LCD_D2    (GPIO_NUM_15)
#define LCD_D3    (GPIO_NUM_10)
#define LCD_D4    (GPIO_NUM_8)
#define LCD_D5    (GPIO_NUM_7)
#define LCD_D6    (GPIO_NUM_6)
#define LCD_D7    (GPIO_NUM_5)

#define CAM_XCLK  (GPIO_NUM_40)
#define CAM_PCLK  (GPIO_NUM_11)
#define CAM_VSYNC (GPIO_NUM_21)
#define CAM_HREF  (GPIO_NUM_38)

#define CAM_D0    (GPIO_NUM_13)
#define CAM_D1    (GPIO_NUM_47)
#define CAM_D2    (GPIO_NUM_14)
#define CAM_D3    (GPIO_NUM_3)
#define CAM_D4    (GPIO_NUM_12)
#define CAM_D5    (GPIO_NUM_42)
#define CAM_D6    (GPIO_NUM_41)
#define CAM_D7    (GPIO_NUM_39)

#define I2C_SCL   (GPIO_NUM_18)
#define I2C_SDA   (GPIO_NUM_17)

#define CAM_PWD   (-1)
#define CAM_RST   (-1)

#ifdef __cplusplus
}
#endif