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
#include "st7789.h"
#include "jpeg.h"
#include "config.h"
#include "ft5x06.h"
#include "gui.h"
#include "esp_lua.h"
#include "esp_lua_lib.h"

static const char *TAG = "main";

lcd_cam_handle_t lcd_cam;
st7789_handle_t st7789;
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
        .horizontal = 2, // 2: UP, 3： DOWN
        .dis_invert = true,
        .dis_bgr = false,
        .write_cb = lcd_cam.lcd.write_data,
    };
    st7789_init(&st7789, &st7789_config);
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
static void lv_disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    uint32_t len = (sizeof(uint16_t) * ((area->y2 - area->y1 + 1)*(area->x2 - area->x1 + 1)));
    st7789.set_index(area->x1, area->y1, area->x2, area->y2);
    lcd_cam.lcd.swap_data(false);
    st7789.write_data((uint8_t *)color_p, len);
    lcd_cam.lcd.swap_data(true);
    lv_disp_flush_ready(disp_drv);
}

static bool lv_disp_input(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint16_t x = 0, y = 0;
    // if (ft5x06_pos_read(&x, &y)) {
    //     data->state = LV_INDEV_STATE_PR;
    // } else {
    //     data->state =  LV_INDEV_STATE_REL;
    // }
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
    draw_buf_1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * (LCD_WIDTH * LCD_HIGH / 2), MALLOC_CAP_INTERNAL); /*A screen sized buffer*/
    lv_disp_buf_init(&disp_buf, draw_buf_1, NULL, LCD_WIDTH * LCD_HIGH / 2);   /*Initialize the display buffer*/

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
    while(1) {
        lv_task_handler();
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}

static const luaL_Reg mylibs[] = {
    {"sys", esp_lib_sys},
    {"net", esp_lib_net},
    {"web", esp_lib_web},
    {"mqtt", esp_lib_mqtt},
    {"httpd", esp_lib_httpd},
    {"ramf", esp_lib_ramf},
    {NULL, NULL}
};

const char LUA_SCRIPT_INIT[] = " \
assert(sys.init()) \
dofile(\'/lua/init.lua\') \
";

void lua_task(void *arg)
{
    char *ESP_LUA_ARGV[5] = {"./lua", "-i", "-e", LUA_SCRIPT_INIT, NULL}; // enter interactive mode after executing 'script'

    esp_lua_init(NULL, NULL, mylibs);

    while (1) {
        esp_lua_main(4, ESP_LUA_ARGV);
        printf("lua exit\n");
        vTaskDelay(2000 / portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}

void app_main() 
{
    esp_log_level_set("*", ESP_LOG_ERROR);
    xTaskCreate(lua_task, "lua_task", 10240, NULL, 5, NULL);
    xTaskCreate(gui_task, "gui_task", 8192, NULL, 5, NULL);
}