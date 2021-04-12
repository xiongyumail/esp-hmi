#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "lcd_cam.h"
#include "st7789.h"
#include "config.h"

static const char *TAG = "main";

#define LCD_RATE_TEST   (1)

static void lcd_cam_task(void *arg)
{
    lcd_cam_handle_t lcd_cam;
    lcd_cam_config_t lcd_cam_config = {
        .lcd = {
            .en = true,
            .width = LCD_BIT,
            .fre = LCD_FRE,
            .pin = {
                .clk  = LCD_CLK,
                .data = {LCD_MOSI},
            },
            .invert = {
                .clk  = false,
                .data = {false},
            },
            .max_dma_buffer_size = 8 * 1024,
            .swap_data = true
        },
    };

    lcd_cam_init(&lcd_cam, &lcd_cam_config);

    st7789_handle_t st7789;
    st7789_config_t st7789_config = {
        .width = LCD_BIT,
        .pin = {
            .dc  = LCD_DC,
            .rd = LCD_RD,
            .cs = LCD_CS,
            .rst = LCD_RST,
            .bk = LCD_BK,
        },
        .invert = {
            .dc  = false,
            .rd = false,
            .cs = false,
            .rst = false,
            .bk = false,
        },
        .horizontal = 0, // 2: UP, 3： DOWN
        .dis_invert = true,
        .dis_bgr = false,
        .write_cb = lcd_cam.lcd.write_data,
    };
    st7789_init(&st7789, &st7789_config);

    uint8_t *img_buf = (uint8_t *)heap_caps_malloc(sizeof(uint16_t) * LCD_WIDTH * LCD_HIGH, MALLOC_CAP_INTERNAL);

    extern const uint8_t pic[];
    for (int y = 0; y < LCD_HIGH; y++) {
        for (int x = 0; x < LCD_WIDTH * 2; x++) {
            img_buf[y * (LCD_WIDTH * 2) + x] = pic[y * (800 * 2) + x];
        }  
    }
    st7789.set_index(0, 0, LCD_WIDTH - 1, LCD_HIGH - 1);
    lcd_cam.lcd.swap_data(false);
    st7789.write_data((uint8_t *)img_buf, LCD_WIDTH * LCD_HIGH * 2);
    lcd_cam.lcd.swap_data(true);
    uint32_t ticks_now = 0, ticks_last = 0;
    struct timeval now;   
    while (LCD_RATE_TEST) {
        gettimeofday(&now, NULL);
        ticks_last = now.tv_sec * 1000 + now.tv_usec / 1000;
        st7789.set_index(0, 0, LCD_WIDTH - 1, LCD_HIGH - 1);
        lcd_cam.lcd.swap_data(false);
        st7789.write_data((uint8_t *)img_buf, LCD_WIDTH * LCD_HIGH * 2);
        lcd_cam.lcd.swap_data(true);
        gettimeofday(&now, NULL);
        ticks_now = now.tv_sec * 1000 + now.tv_usec / 1000;
        if (ticks_now - ticks_last > 0) {
            printf("fps: %.2f\n", 1000.0 / (int)(ticks_now - ticks_last));
        }
    }
    free(img_buf);

    st7789_deinit(&st7789);
    lcd_cam_deinit(&lcd_cam);
    vTaskDelete(NULL);
}

void app_main() 
{
    xTaskCreate(lcd_cam_task, "lcd_cam_task", 4096, NULL, 5, NULL);
}