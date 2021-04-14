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
	lv_obj_t *screen_cont8;
	lv_obj_t *screen_doggie_1;
	lv_obj_t *screen_clock_lable;
	lv_obj_t *screen_header;
	lv_obj_t *screen_heade_power;
	lv_obj_t *screen_heade_net;
	lv_obj_t *screen_heade_state;
	lv_obj_t *screen_clock_s_lable;
	lv_obj_t *screen_date;
	lv_obj_t *screen_week;
	lv_obj_t *screen_line10;
	lv_obj_t *screen_line11;
	lv_obj_t *screen_line10_12;
	lv_obj_t *screen_line13;
	lv_obj_t *screen_label14;
	lv_obj_t *screen_label15;
	lv_obj_t *screen_img16;
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