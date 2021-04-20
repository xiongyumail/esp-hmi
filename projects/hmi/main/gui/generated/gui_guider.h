/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	lv_obj_t *screen_main_cont;
	lv_obj_t *screen_image;
	lv_obj_t *screen_header;
	lv_obj_t *screen_power;
	lv_obj_t *screen_net;
	lv_obj_t *screen_state;
	lv_obj_t *screen_clock;
	lv_obj_t *screen_clock_s;
	lv_obj_t *screen_date_y;
	lv_obj_t *screen_date_md;
	lv_obj_t *screen_date_w;
	lv_obj_t *screen_weather_image;
	lv_obj_t *screen_weather;
	lv_obj_t *screen_temp;
	lv_obj_t *screen_line10;
	lv_obj_t *screen_line11;
	lv_obj_t *screen_line10_12;
	lv_obj_t *screen_line11_17;
	lv_obj_t *screen_line10_18;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
LV_IMG_DECLARE(_sun_alpha_64x64);
LV_IMG_DECLARE(_doggie_1_alpha_100x100);

#ifdef __cplusplus
}
#endif
#endif