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
#include "ov2640.h"
#include "ov3660.h"
#include "sensor.h"
#include "sccb.h"
#include "driver/gpio.h"
#include "lcd_cam.h"
#include "st7796.h"
#include "jpeg.h"
#include "config.h"
#include "ft5x06.h"

static const char *TAG = "main";

#define LCD_RATE_TEST   (0)
#define LCD_TOUCH_TEST  (0)
#define CAM_JPEG_MODE   (0)
#define CAM_YUV_MODE    (0)
#define CAM_JPEG_ENCODE (0)

static void lcd_cam_task(void *arg)
{
    lcd_cam_handle_t lcd_cam;
    lcd_cam_config_t lcd_cam_config = {
        .lcd = {
            .en = true,
            .width = LCD_BIT,
            .fre = LCD_FRE,
            .pin = {
                .clk  = LCD_WR,
                .data = {LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7},
            },
            .invert = {
                .clk  = false,
                .data = {false, false, false, false, false, false, false, false},
            },
            .max_dma_buffer_size = 32 * 1024,
            .swap_data = true
        },
        .cam = {
            .en = true,
            .width = CAM_BIT,
            .fre = CAM_FRE,
            .pin = {
                .xclk  = CAM_XCLK,
                .pclk  = CAM_PCLK,
                .vsync = CAM_VSYNC,
                .href = CAM_HREF,
                .data = {CAM_D0, CAM_D1, CAM_D2, CAM_D3, CAM_D4, CAM_D5, CAM_D6, CAM_D7},
            },
            .invert = {
                .xclk  = false,
                .pclk  = false,
                .vsync = true,
                .href = false,
                .data = {false, false, false, false, false, false, false, false},
            },
            .mode.jpeg = CAM_JPEG_MODE,
            .recv_size = CAM_WIDTH * CAM_HIGH * 2,
            .max_dma_buffer_size = 16 * 1024,
            .frame_cnt = 2, 
            .frame_caps = MALLOC_CAP_SPIRAM,
            .task_stack = 1024,
            .task_pri = configMAX_PRIORITIES,
            .swap_data = false
        }
    };

    lcd_cam_init(&lcd_cam, &lcd_cam_config);

    st7796_handle_t st7796;
    st7796_config_t st7796_config = {
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
    st7796_init(&st7796, &st7796_config);

    uint8_t *img_buf = (uint8_t *)heap_caps_malloc(sizeof(uint16_t) * LCD_WIDTH * LCD_HIGH, MALLOC_CAP_SPIRAM);

    extern const uint8_t pic[];
    for (int y = 0; y < LCD_HIGH; y++) {
        for (int x = 0; x < LCD_WIDTH * 2; x++) {
            img_buf[y * (LCD_WIDTH * 2) + x] = pic[y * (800 * 2) + x];
        }  
    }
    st7796.set_index(0, 0, LCD_WIDTH - 1, LCD_HIGH - 1);
    lcd_cam.lcd.swap_data(false);
    st7796.write_data((uint8_t *)img_buf, LCD_WIDTH * LCD_HIGH * 2);
    lcd_cam.lcd.swap_data(true);
    uint32_t ticks_now = 0, ticks_last = 0;
    struct timeval now;   
    while (LCD_RATE_TEST) {
        gettimeofday(&now, NULL);
        ticks_last = now.tv_sec * 1000 + now.tv_usec / 1000;
        st7796.set_index(0, 0, LCD_WIDTH - 1, LCD_HIGH - 1);
        lcd_cam.lcd.swap_data(false);
        st7796.write_data((uint8_t *)img_buf, LCD_WIDTH * LCD_HIGH * 2);
        lcd_cam.lcd.swap_data(true);
        gettimeofday(&now, NULL);
        ticks_now = now.tv_sec * 1000 + now.tv_usec / 1000;
        if (ticks_now - ticks_last > 0) {
            printf("fps: %.2f\n", 1000.0 / (int)(ticks_now - ticks_last));
        }
    }
    free(img_buf);
#if CAM_JPEG_ENCODE
    uint8_t *jpeg_buf = (uint8_t *)heap_caps_malloc(CAM_WIDTH * CAM_HIGH * sizeof(uint16_t), MALLOC_CAP_SPIRAM);
#endif

    if (CAM_PWD != -1 && CAM_RST != -1) {
        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_DISABLE;
        io_conf.mode = GPIO_MODE_OUTPUT;
        io_conf.pin_bit_mask = (1ULL << CAM_PWD) | (1ULL << CAM_RST);
        io_conf.pull_down_en = 0;
        io_conf.pull_up_en = 0;
        gpio_config(&io_conf);

        gpio_set_level(CAM_PWD, 0);
        gpio_set_level(CAM_RST, 1);
    }

    sensor_t sensor;
    SCCB_Init(CAM_SDA, CAM_SCL);
    ft5x06_init();
    while (LCD_TOUCH_TEST) {
        uint16_t xpos, ypos;
        ft5x06_pos_read(&xpos, &ypos);
        printf("xpos: %d, ypos: %d\n", xpos, ypos);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
    sensor.slv_addr = SCCB_Probe();
    ESP_LOGI(TAG, "sensor_id: 0x%x\n", sensor.slv_addr);
    sensor.slv_addr = 0x3c;
    if (sensor.slv_addr == 0x30) { // OV2640
        if (OV2640_Init(0, 1) != 0) {
            goto fail;
        }
#if CAM_JPEG_MODE
    OV2640_JPEG_Mode();
#else
#if CAM_YUV_MODE
    OV2640_YUV_Mode();
#else
    OV2640_RGB565_Mode(false);    //RGB565模式
#endif
#endif
        OV2640_ImageSize_Set(800, 600);
        OV2640_ImageWin_Set(0, 0, 800, 600);
        OV2640_OutSize_Set(CAM_WIDTH, CAM_HIGH); 
    } else if (sensor.slv_addr == 0x3C) { // OV3660
        ov3660_init(&sensor);
        sensor.init_status(&sensor);
        if (sensor.reset(&sensor) != 0) {
            goto fail;
        }
#if CAM_JPEG_MODE
    sensor.set_pixformat(&sensor, PIXFORMAT_JPEG);
#else
#if CAM_YUV_MODE
    sensor.set_pixformat(&sensor, PIXFORMAT_YUV422);
#else
    sensor.set_pixformat(&sensor, PIXFORMAT_RGB565);
#endif
#endif
        // totalX 变小，帧率提高
        // totalY 变小，帧率提高vsync 变短
        sensor.set_res_raw(&sensor, 0, 0, 2079, 1547, 8, 2, 2000, 800, CAM_WIDTH, CAM_HIGH, true, true);
        sensor.set_vflip(&sensor, 1);
        sensor.set_hmirror(&sensor, 1);
        sensor.set_pll(&sensor, false, 15, 1, 0, false, 0, true, 5); // 39 fps
    } else {
        ESP_LOGE(TAG, "sensor is temporarily not supported\n");
        goto fail;
    }

    ESP_LOGI(TAG, "camera init done\n");
    vTaskDelay(1000 / portTICK_RATE_MS);
    lcd_cam.cam.start();
    while (1) {
        gettimeofday(&now, NULL);
        ticks_last = now.tv_sec * 1000 + now.tv_usec / 1000;
        uint8_t *cam_buf = NULL;
        size_t recv_len = 0;
        recv_len = lcd_cam.cam.take(&cam_buf);
#if CAM_JPEG_MODE
        printf("total_len: %d\n", recv_len);
        for (int x = 0; x < 10; x++) {
            ets_printf("%d ", cam_buf[x]);
        }
        ets_printf("\n");

        int w, h;
        uint8_t *img = jpeg_decode(cam_buf, &w, &h);
        if (img) {
            ESP_LOGI(TAG, "jpeg: w: %d, h: %d\n", w, h);
            st7796.set_index(0, 0, w - 1, h - 1);
            st7796.write_data(img, w * h * sizeof(uint16_t));
            free(img);
        }
#else
#if CAM_JPEG_ENCODE
        int jpeg_len = jpeg_encode(CAM_YUV_MODE ? ENCODE_YUV_MODE: ENCODE_RGB16_MODE, cam_buf, CAM_WIDTH, CAM_HIGH, jpeg_buf, CAM_WIDTH * CAM_HIGH * sizeof(uint16_t));

        printf("jpeg_len: %d\n", jpeg_len);
        for (int x = 0; x < 10; x++) {
            ets_printf("%d ", jpeg_buf[x]);
        }
        ets_printf("\n");

        int w, h;
        uint8_t *img = jpeg_decode(jpeg_buf, &w, &h);
        if (img) {
            ESP_LOGI(TAG, "jpeg: w: %d, h: %d\n", w, h);
            st7796.set_index(0, 0, w - 1, h - 1);
            st7796.write_data(img, w * h * sizeof(uint16_t));
            free(img);
        }
#else
        st7796.set_index(0, 0, CAM_WIDTH - 1, CAM_HIGH - 1);
        st7796.write_data(cam_buf, CAM_WIDTH * CAM_HIGH * 2);
#endif
#endif
        lcd_cam.cam.give(cam_buf);   
        gettimeofday(&now, NULL);
        ticks_now = now.tv_sec * 1000 + now.tv_usec / 1000;
        if (ticks_now - ticks_last > 0) {
            printf("fps: %.2f\n", 1000.0 / (int)(ticks_now - ticks_last));
        }
    }

fail:
    st7796_deinit(&st7796);
    lcd_cam_deinit(&lcd_cam);
    vTaskDelete(NULL);
}

void app_main() 
{
    xTaskCreate(lcd_cam_task, "lcd_cam_task", 4096, NULL, 5, NULL);
}