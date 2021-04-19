#include "gui.h"
#include "gui_guider.h"
#include "events_init.h"

lv_ui guider_ui;

int gui_init(lv_disp_t **disp_array, lv_indev_t **indev_array, lv_theme_t * th)
{
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

    return 0;
}

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
                    lv_label_set_text(wifi, LV_SYMBOL_WIFI);
                } else {
                    lv_label_set_text(wifi, "");
                } 
            }
            break;

            case GUI_STATE_EVENT: {
                lv_label_set_text(state, text);
            }
            break;

            case GUI_BATTERY_EVENT: {
                switch (atoi(text)) {
                    case BATTERY_FULL: {
                        lv_label_set_text(battery, LV_SYMBOL_BATTERY_FULL);
                    }
                    break;

                    case BATTERY_3: {
                        lv_label_set_text(battery, LV_SYMBOL_BATTERY_3);
                    }
                    break;

                    case BATTERY_2: {
                        lv_label_set_text(battery, LV_SYMBOL_BATTERY_2);
                    }
                    break;

                    case BATTERY_1: {
                        lv_label_set_text(battery, LV_SYMBOL_BATTERY_1);
                    }
                    break;

                    case BATTERY_EMPTY: {
                        lv_label_set_text(battery, LV_SYMBOL_BATTERY_EMPTY);
                    }
                    break;

                    case BATTERY_CHARGE: {
                        lv_label_set_text(battery, LV_SYMBOL_CHARGE);
                    }
                    break;
                }
            }
            break;

            case GUI_MSG_EVENT: {
                lv_label_set_text(message, text);
            }
            break;

            case GUI_IMG_EVENT: {
                if (strncmp(text, ESP_LUA_RAM_FILE_PATH, strlen(ESP_LUA_RAM_FILE_PATH)) == 0) {
                    esp_lua_ramf_t *ramf = (esp_lua_ramf_t *)atoi(&text[strlen(ESP_LUA_RAM_FILE_PATH)]);
                    ramf_img.data = ramf->data;
                    ramf_img.data_size = ramf->size;
                    uint32_t size[2];
                    memcpy(size, ramf_img.data + 16, 8);
                    
                    /*The width and height are stored in Big endian format so convert them to little endian*/
                    ramf_img.header.w = (lv_coord_t) ((size[0] & 0xff000000) >> 24) +  ((size[0] & 0x00ff0000) >> 8);
                    ramf_img.header.h = (lv_coord_t) ((size[1] & 0xff000000) >> 24) +  ((size[1] & 0x00ff0000) >> 8);
                    lv_img_set_src(img, &ramf_img);
                } else {
                    lv_img_set_src(img, text);
                }
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
    } else if (strcmp(io, "STATE") == 0) {
        event = GUI_STATE_EVENT;
    } else if (strcmp(io, "MSG") == 0) {
        event = GUI_MSG_EVENT;
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