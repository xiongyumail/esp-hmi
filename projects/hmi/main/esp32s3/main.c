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
#include "lcd_cam.h"
#include "st7796.h"
#include "jpeg.h"
#include "config.h"
#include "ft5x06.h"
#include "gui.h"

static const char *TAG = "main";

#define MOUNT_POINT "/sdcard"

#define CAM_JPEG_MODE   (0)

lcd_cam_handle_t lcd_cam;
st7796_handle_t st7796;
static lv_disp_t *disp[1];
static lv_disp_t *indev[1];

/* Initialize your display and the required peripherals. */
static void lv_disp_init(void)
{
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
            .max_dma_buffer_size = 8 * 1024,
            .swap_data = true
        },
        .cam = {
            .en = false,
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
        .horizontal = 2, // 2: UP, 3： DOWN
        .dis_invert = true,
        .dis_bgr = false,
        .write_cb = lcd_cam.lcd.write_data,
    };
    st7796_init(&st7796, &st7796_config);
    SCCB_Init(I2C_SDA, I2C_SCL);
    ft5x06_init();
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
static void lv_disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    uint32_t len = (sizeof(uint16_t) * ((area->y2 - area->y1 + 1)*(area->x2 - area->x1 + 1)));
    st7796.set_index(area->x1, area->y1, area->x2, area->y2);
    lcd_cam.lcd.swap_data(false);
    st7796.write_data((uint8_t *)color_p, len);
    lcd_cam.lcd.swap_data(true);
    lv_disp_flush_ready(disp_drv);
}

static bool lv_disp_input(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint16_t x = 0, y = 0;
    if (ft5x06_pos_read(&x, &y)) {
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state =  LV_INDEV_STATE_REL;
    }
    data->point.x = LV_HOR_RES_MAX - y;   
    data->point.y = x;
    return false; /*No buffering so no more data read*/
}

static void lv_memory_monitor(lv_task_t * param)
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

static void lv_tick_task(void * arg)
{
    while(1) {
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
    draw_buf_1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * (LV_HOR_RES_MAX * LV_VER_RES_MAX / 2), MALLOC_CAP_INTERNAL); /*A screen sized buffer*/
    lv_disp_buf_init(&disp_buf, draw_buf_1, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 2);   /*Initialize the display buffer*/

    /*Create a display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.buffer = &disp_buf;
    disp_drv.flush_cb = lv_disp_flush;    /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    disp[0] = lv_disp_drv_register(&disp_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lv_disp_input;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev[0] = lv_indev_drv_register(&indev_drv);
    
    lv_disp_set_default(disp[0]);

    lv_task_create(lv_memory_monitor, 3000, LV_TASK_PRIO_MID, NULL);

    gui_init(disp, indev, NULL);
    while(1) {
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
    sdmmc_card_t* card;
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
    FILE* f = fopen(MOUNT_POINT"/hello.txt", "w");
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
    char* pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI(TAG, "Read from file: '%s'", line);
#endif

    return ESP_OK;
}

void app_main() 
{
    sd_init();
    
    xTaskCreate(gui_task, "gui_task", 8192, NULL, 5, NULL);
}