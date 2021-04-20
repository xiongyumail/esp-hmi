#include <stdio.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "gui.h"
#include "gui_guider.h"
#include "events_init.h"

typedef struct {
    int event;
    void *arg;
} gui_event_t;

#define GUI_WIFI_EVENT 0
#define GUI_BATTERY_EVENT 1
#define GUI_CLOCK_EVENT 2
#define GUI_DATE_EVENT 3
#define GUI_WEATHER_EVENT 4
#define GUI_TEMP_EVENT 5
#define GUI_IMG_EVENT 6

static QueueHandle_t gui_event_queue = NULL;

lv_ui guider_ui;

static void gui_task(lv_task_t * arg)
{
    int ret;
    gui_event_t e;
    while (1) {
        ret = xQueueReceive(gui_event_queue, &e, 0);
        if (ret == pdFALSE) {
            break;
        }
        char *text = (char *)e.arg;
        switch (e.event) {
            case GUI_WIFI_EVENT: {
                if (atoi(text) == 1) {
                    lv_label_set_text(guider_ui.screen_net, LV_SYMBOL_WIFI);
                } else {
                    lv_label_set_text(guider_ui.screen_net, "");
                } 
            }
            break;

            case GUI_CLOCK_EVENT: {
                char clock[16];
                memcpy(clock, &text[0], 5);
                clock[5] = '\0';
                lv_label_set_text(guider_ui.screen_clock, clock);
                memcpy(clock, &text[6], 2);
                clock[2] = '\0';
                lv_label_set_text(guider_ui.screen_clock_s, clock);
            }
            break;

            case GUI_DATE_EVENT: {
                char date[16];
                sprintf(date, "%d年", atoi(&text[0]));
                lv_label_set_text(guider_ui.screen_date_y, date);
                sprintf(date, "%d月%d日", atoi(&text[5]), atoi(&text[8]));
                lv_label_set_text(guider_ui.screen_date_md, date);
                switch (atoi(&text[11])) {
                    case 0: sprintf(date, "周日"); break;
                    case 1: sprintf(date, "周一"); break;
                    case 2: sprintf(date, "周二"); break;
                    case 3: sprintf(date, "周三"); break;
                    case 4: sprintf(date, "周四"); break;
                    case 5: sprintf(date, "周五"); break;
                    case 6: sprintf(date, "周六"); break;
                }
                lv_label_set_text(guider_ui.screen_date_w, date);
            }
            break;

            case GUI_BATTERY_EVENT: {
                switch (atoi(text)) {
                    case BATTERY_FULL: {
                        lv_label_set_text(guider_ui.screen_power, LV_SYMBOL_BATTERY_FULL);
                    }
                    break;

                    case BATTERY_3: {
                        lv_label_set_text(guider_ui.screen_power, LV_SYMBOL_BATTERY_3);
                    }
                    break;

                    case BATTERY_2: {
                        lv_label_set_text(guider_ui.screen_power, LV_SYMBOL_BATTERY_2);
                    }
                    break;

                    case BATTERY_1: {
                        lv_label_set_text(guider_ui.screen_power, LV_SYMBOL_BATTERY_1);
                    }
                    break;

                    case BATTERY_EMPTY: {
                        lv_label_set_text(guider_ui.screen_power, LV_SYMBOL_BATTERY_EMPTY);
                    }
                    break;

                    case BATTERY_CHARGE: {
                        lv_label_set_text(guider_ui.screen_power, LV_SYMBOL_CHARGE);
                    }
                    break;
                }
            }
            break;

            case GUI_WEATHER_EVENT: {
                lv_label_set_text(guider_ui.screen_weather, text);
            }
            break;

            case GUI_TEMP_EVENT: {
                lv_label_set_text(guider_ui.screen_temp, text);
            }
            break;

            case GUI_IMG_EVENT: {
                // if (strncmp(text, ESP_LUA_RAM_FILE_PATH, strlen(ESP_LUA_RAM_FILE_PATH)) == 0) {
                //     esp_lua_ramf_t *ramf = (esp_lua_ramf_t *)atoi(&text[strlen(ESP_LUA_RAM_FILE_PATH)]);
                //     ramf_img.data = ramf->data;
                //     ramf_img.data_size = ramf->size;
                //     uint32_t size[2];
                //     memcpy(size, ramf_img.data + 16, 8);
                    
                //     /*The width and height are stored in Big endian format so convert them to little endian*/
                //     ramf_img.header.w = (lv_coord_t) ((size[0] & 0xff000000) >> 24) +  ((size[0] & 0x00ff0000) >> 8);
                //     ramf_img.header.h = (lv_coord_t) ((size[1] & 0xff000000) >> 24) +  ((size[1] & 0x00ff0000) >> 8);
                //     lv_img_set_src(img, &ramf_img);
                // } else {
                //     lv_img_set_src(img, text);
                // }
            }
            break;
        }
        free(text);
    }
}

static int gui_event_send(int event, void *arg, int ticks_wait)
{
    int ret;
    if (gui_event_queue == NULL) {
        return -1;
    }

    gui_event_t e;
    e.event = event;
    e.arg = arg;
    ret = xQueueSend(gui_event_queue, &e, ticks_wait);
    if (ret == pdFALSE) {
        return -1;
    }

    return 0;
}

int gui_write(char *io, char* str, int ticks_wait) 
{
    int event = 0;

    if (strcmp(io, "WIFI") == 0) {
        event = GUI_WIFI_EVENT;
    } else if (strcmp(io, "BATT") == 0) {
        event = GUI_BATTERY_EVENT;
    } else if (strcmp(io, "CLOCK") == 0) {
        event = GUI_CLOCK_EVENT;
    } else if (strcmp(io, "DATE") == 0) {
        event = GUI_DATE_EVENT;
    } else if (strcmp(io, "WEATHER") == 0) {
        event = GUI_WEATHER_EVENT;
    } else if (strcmp(io, "TEMP") == 0) {
        event = GUI_TEMP_EVENT;
    } else if (strcmp(io, "IMG") == 0) {
        event = GUI_IMG_EVENT;
    } else {
        return -1;
    }

    char *text = (char *)malloc(strlen(str) + 1);
    strcpy(text, str);
    if (gui_event_send(event, text, ticks_wait) == 0) {
        return 0;
    } else {
        free(text);
        return -1;
    }
}

int gui_init(lv_disp_t **disp_array, lv_indev_t **indev_array, lv_theme_t * th)
{
    gui_event_queue = xQueueCreate(10, sizeof(gui_event_t));
    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(esp_icon);                          /*Declare the image file.*/
    lv_obj_t * cursor_obj =  lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &esp_icon);             /*Set the image source*/
    lv_indev_set_cursor(indev_array[0], cursor_obj);               /*Connect the image  object to the driver*/

    // lv_demo_benchmark();

    // lv_demo_music();

    // lv_demo_widgets();

    // lv_demo_stress();

    /*Create a GUI-Guider app */
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    lv_task_create(gui_task, 10, LV_TASK_PRIO_MID, NULL);
    return 0;
}