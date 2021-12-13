#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "ov2640.h"
#include "ov3660.h"
#include "sensor.h"
#include "sccb.h"
#include "driver/gpio.h"
#include "lcd.h"
#include "st7796_rgb.h"
#include "jpeg.h"
#include "config.h"
#include "ft5x06.h"
#include "gt1151.h"
#include "gui.h"
#include "esp32s3/rom/cache.h"

static const char *TAG = "main";

#define MOUNT_POINT "/sdcard"

#define CAM_JPEG_MODE   (0)

lcd_handle_t lcd;
static lv_disp_t *disp[1];
static lv_disp_t *indev[1];

/* Initialize your display and the required peripherals. */
static void lv_disp_init(void)
{
    lcd_create(&lcd);
    lcd.ctrl->bus.fre = LCD_FRE;
    lcd.ctrl->bus.width = LCD_BIT;
    lcd.ctrl->pin_clk.clk = LCD_PCLK;
    lcd.ctrl->pin_clk.clk_inv = 1;
    lcd.ctrl->pin_vsync.vsync = LCD_VSYNC;
    lcd.ctrl->pin_vsync.vsync_inv = 0;
    lcd.ctrl->pin_hsync.hsync = LCD_HSYNC;
    lcd.ctrl->pin_hsync.hsync_inv = 0;
    lcd.ctrl->pin_href.href = LCD_HREF;
    lcd.ctrl->pin_href.href_inv = 0;
    lcd.ctrl->res.x = LCD_WIDTH;
    lcd.ctrl->res.y = LCD_HIGH;
    lcd.ctrl->video_timing_sync.hsync = 20;
    lcd.ctrl->video_timing_sync.vsync = 2;
    lcd.ctrl->video_timing_h.hbp = 30;
    lcd.ctrl->video_timing_h.hfp = 30;
    lcd.ctrl->video_timing_v.vbp = 2;
    lcd.ctrl->video_timing_v.vfp = 2;
    lcd.ctrl->pin_data[0].data = LCD_D0;
    lcd.ctrl->pin_data[1].data = LCD_D1;
    lcd.ctrl->pin_data[2].data = LCD_D2;
    lcd.ctrl->pin_data[3].data = LCD_D3;
    lcd.ctrl->pin_data[4].data = LCD_D4;
    lcd.ctrl->pin_data[5].data = LCD_D5;
    lcd.ctrl->pin_data[6].data = LCD_D6;
    lcd.ctrl->pin_data[7].data = LCD_D7;
    lcd.ctrl->pin_data[8].data = LCD_D8;
    lcd.ctrl->pin_data[9].data = LCD_D9;
    lcd.ctrl->pin_data[10].data = LCD_D10;
    lcd.ctrl->pin_data[11].data = LCD_D11;
    lcd.ctrl->pin_data[12].data = LCD_D12;
    lcd.ctrl->pin_data[13].data = LCD_D13;
    lcd.ctrl->pin_data[14].data = LCD_D14;
    lcd.ctrl->pin_data[15].data = LCD_D15;
    lcd.ctrl->ctr.swap_data = false;
    lcd.ctrl->ctr.frame_buffer_num = 1;
    lcd.ctrl->ctr.mode_sel = 0;
    lcd.ctrl->ctr.max_cp_buffer_size = 0;
    lcd.ctrl->ctr.pix_bytes = 2;

    for (int x = 0; x < lcd.ctrl->ctr.frame_buffer_num; x++) {
        lcd.ctrl->frame_buffer[x].addr = (uint8_t *)heap_caps_malloc(LCD_WIDTH * LCD_HIGH * sizeof(uint16_t), MALLOC_CAP_SPIRAM); // 保证字节对齐

        if (lcd.ctrl->frame_buffer[x].addr == NULL) {
            ESP_LOGE(TAG, "frame_buffer malloc fail!");

            for (int x = 0; x < lcd.ctrl->ctr.frame_buffer_num; x++) {
                free(lcd.ctrl->frame_buffer[x].addr);
            }

            lcd_remove(&lcd);
            return;
        }
    }

    lcd_config(&lcd);

    lcd.port->ctr.slv.run(&lcd);
    lcd.port->fb.slv.write(&lcd, 0);

    SCCB_Init(I2C_SDA, I2C_SCL);
    // ft5x06_init();
    gt1151_init();
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
static void lv_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t hlen = (area->x2 - area->x1 + 1) * sizeof(uint16_t);
    uint32_t len = (sizeof(uint16_t) * ((area->y2 - area->y1 + 1) * (area->x2 - area->x1 + 1)));

    uint8_t *frame_buffer = lcd.ctrl->frame_buffer[0].addr;
    int cnt = 0;
    int index = 0;

    cnt = 0;

    for (int y = area->y1; y <= area->y2; y++) {
        index = (y * LCD_WIDTH + area->x1) * 2 ;
        memcpy(&frame_buffer[index], &color_p[cnt].full, hlen);
        cnt += hlen >> 1;
    }

    // vTaskDelay(10 / portTICK_PERIOD_MS);
    Cache_WriteBack_Addr(frame_buffer, LCD_WIDTH * LCD_HIGH * 2);

    lv_disp_flush_ready(disp_drv);
}

static bool lv_disp_input(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    static uint16_t x = 0, y = 0;

    // if (ft5x06_pos_read(&x, &y)) {
    if (gt1151_pos_read(&x, &y)) {
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state =  LV_INDEV_STATE_REL;
    }

    data->point.x = x;
    data->point.y = y;
    return false; /*No buffering so no more data read*/
}

static void lv_memory_monitor(lv_task_t *param)
{
    (void) param; /*Unused*/

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    ESP_LOGI(TAG, "used: %6d (%3d %%), frag: %3d %%, biggest free: %6d, system free: %d/%d\n", (int)mon.total_size - mon.free_size,
             mon.used_pct,
             mon.frag_pct,
             (int)mon.free_biggest_size,
             heap_caps_get_free_size(MALLOC_CAP_INTERNAL), esp_get_free_heap_size());
}

static void lv_tick_task(void *arg)
{
    while (1) {
        lv_tick_inc(10);
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}

static void gui_task(void *arg)
{
    xTaskCreate(lv_tick_task, "lv_tick_task", 1024, NULL, 5, NULL);

    lv_disp_init();

    lv_init();

    static lv_disp_buf_t disp_buf;
    static lv_color_t *draw_buf_1 = NULL;
    static lv_color_t *draw_buf_2 = NULL;
    draw_buf_1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * (LCD_WIDTH * LCD_HIGH / 4), MALLOC_CAP_INTERNAL); /*A screen sized buffer*/
    lv_disp_buf_init(&disp_buf, draw_buf_1, NULL, LCD_WIDTH * LCD_HIGH / 4);   /*Initialize the display buffer*/

    /*Create a display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.buffer = &disp_buf;
    disp_drv.flush_cb = lv_disp_flush;    /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HIGH;
    disp[0] = lv_disp_drv_register(&disp_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lv_disp_input;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev[0] = lv_indev_drv_register(&indev_drv);

    lv_disp_set_default(disp[0]);

    lv_task_create(lv_memory_monitor, 3000, LV_TASK_PRIO_MID, NULL);

    gui_init(disp, indev, NULL);

    while (1) {
        lv_task_handler();
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}

esp_err_t sd_init()
{
    esp_err_t ret;
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t *card;
    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(TAG, "Initializing SD card");
    ESP_LOGI(TAG, "Using SDMMC peripheral");

    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    // use 1-line SD mode
    slot_config.width = 1;
    slot_config.clk = 9;
    slot_config.cmd = 20;
    slot_config.d0 = 19;
    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. ");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }

        return ret;
    }

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);

#if 0
    ESP_LOGI(TAG, "Opening file");
    FILE *f = fopen(MOUNT_POINT"/hello.txt", "w");

    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }

    fprintf(f, "Hello %s!\n", card->cid.name);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    // Check if destination file exists before renaming
    struct stat st;

    if (stat(MOUNT_POINT"/foo.txt", &st) == 0) {
        // Delete it if it exists
        unlink(MOUNT_POINT"/foo.txt");
    }

    // Rename original file
    ESP_LOGI(TAG, "Renaming file");

    if (rename(MOUNT_POINT"/hello.txt", MOUNT_POINT"/foo.txt") != 0) {
        ESP_LOGE(TAG, "Rename failed");
        return;
    }

    // Open renamed file for reading
    ESP_LOGI(TAG, "Reading file");
    f = fopen(MOUNT_POINT"/foo.txt", "r");

    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }

    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    // strip newline
    char *pos = strchr(line, '\n');

    if (pos) {
        *pos = '\0';
    }

    ESP_LOGI(TAG, "Read from file: '%s'", line);
#endif

    return ESP_OK;
}

void app_main()
{
    // sd_init();
    xTaskCreate(gui_task, "gui_task", 8192, NULL, 5, NULL);
}