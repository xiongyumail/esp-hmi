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
	lv_obj_t *screen_btn0;
	lv_obj_t *screen_btn0_label;
	lv_obj_t *screen_btn1;
	lv_obj_t *screen_btn1_label;
	lv_obj_t *screen_btn2;
	lv_obj_t *screen_btn2_label;
	lv_obj_t *screen_label3;
	lv_obj_t *screen_btn4;
	lv_obj_t *screen_btn4_label;
	lv_obj_t *screen_label5;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif