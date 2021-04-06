/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL, NULL);
	lv_anim_path_t lv_anim_path_screen_btn0 = {.cb = lv_anim_path_overshoot};

	//Write codes screen_btn0
	ui->screen_btn0 = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_btn0
	static lv_style_t style_screen_btn0_main;
	lv_style_init(&style_screen_btn0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn0_main
	lv_style_set_radius(&style_screen_btn0_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_btn0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_btn0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_btn0_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btn0_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_btn0_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_btn0_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_btn0_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_btn0_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_screen_btn0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_btn0, LV_BTN_PART_MAIN, &style_screen_btn0_main);
	lv_obj_set_pos(ui->screen_btn0, 0, 93);
	lv_obj_set_size(ui->screen_btn0, 100, 50);

	//Write animation: screen_btn0move in x direction
	lv_anim_t screen_btn0_x;
	lv_anim_init(&screen_btn0_x);
	lv_anim_set_var(&screen_btn0_x, ui->screen_btn0);
	lv_anim_set_time(&screen_btn0_x, 1000);
	lv_anim_set_exec_cb(&screen_btn0_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
	lv_anim_set_values(&screen_btn0_x, lv_obj_get_x(ui->screen_btn0), 110);
	_lv_memcpy_small(&screen_btn0_x.path, &lv_anim_path_screen_btn0, sizeof(lv_anim_path_cb_t));
	lv_anim_start(&screen_btn0_x);
	ui->screen_btn0_label = lv_label_create(ui->screen_btn0, NULL);
	lv_label_set_text(ui->screen_btn0_label, "benchmark");
	lv_obj_set_style_local_text_color(ui->screen_btn0_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_btn0_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_anim_path_t lv_anim_path_screen_btn1 = {.cb = lv_anim_path_overshoot};

	//Write codes screen_btn1
	ui->screen_btn1 = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_btn1
	static lv_style_t style_screen_btn1_main;
	lv_style_init(&style_screen_btn1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn1_main
	lv_style_set_radius(&style_screen_btn1_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_btn1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_btn1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_btn1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btn1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_btn1_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_btn1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_btn1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_btn1_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_screen_btn1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_btn1, LV_BTN_PART_MAIN, &style_screen_btn1_main);
	lv_obj_set_pos(ui->screen_btn1, 220, 198);
	lv_obj_set_size(ui->screen_btn1, 100, 50);

	//Write animation: screen_btn1move in x direction
	lv_anim_t screen_btn1_x;
	lv_anim_init(&screen_btn1_x);
	lv_anim_set_var(&screen_btn1_x, ui->screen_btn1);
	lv_anim_set_time(&screen_btn1_x, 1000);
	lv_anim_set_exec_cb(&screen_btn1_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
	lv_anim_set_values(&screen_btn1_x, lv_obj_get_x(ui->screen_btn1), 110);
	_lv_memcpy_small(&screen_btn1_x.path, &lv_anim_path_screen_btn1, sizeof(lv_anim_path_cb_t));
	lv_anim_start(&screen_btn1_x);
	ui->screen_btn1_label = lv_label_create(ui->screen_btn1, NULL);
	lv_label_set_text(ui->screen_btn1_label, "music");
	lv_obj_set_style_local_text_color(ui->screen_btn1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_btn1_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_anim_path_t lv_anim_path_screen_btn2 = {.cb = lv_anim_path_overshoot};

	//Write codes screen_btn2
	ui->screen_btn2 = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_btn2
	static lv_style_t style_screen_btn2_main;
	lv_style_init(&style_screen_btn2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn2_main
	lv_style_set_radius(&style_screen_btn2_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_btn2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_btn2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_btn2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btn2_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_btn2_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_btn2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_btn2_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_btn2_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_screen_btn2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_btn2, LV_BTN_PART_MAIN, &style_screen_btn2_main);
	lv_obj_set_pos(ui->screen_btn2, 0, 302);
	lv_obj_set_size(ui->screen_btn2, 100, 50);

	//Write animation: screen_btn2move in x direction
	lv_anim_t screen_btn2_x;
	lv_anim_init(&screen_btn2_x);
	lv_anim_set_var(&screen_btn2_x, ui->screen_btn2);
	lv_anim_set_time(&screen_btn2_x, 1000);
	lv_anim_set_exec_cb(&screen_btn2_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
	lv_anim_set_values(&screen_btn2_x, lv_obj_get_x(ui->screen_btn2), 110);
	_lv_memcpy_small(&screen_btn2_x.path, &lv_anim_path_screen_btn2, sizeof(lv_anim_path_cb_t));
	lv_anim_start(&screen_btn2_x);
	ui->screen_btn2_label = lv_label_create(ui->screen_btn2, NULL);
	lv_label_set_text(ui->screen_btn2_label, "widgets");
	lv_obj_set_style_local_text_color(ui->screen_btn2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_btn2_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);

	//Write codes screen_label3
	ui->screen_label3 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label3, "Demo 选择");
	lv_label_set_long_mode(ui->screen_label3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label3, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label3
	static lv_style_t style_screen_label3_main;
	lv_style_init(&style_screen_label3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label3_main
	lv_style_set_radius(&style_screen_label3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label3_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label3_main, LV_STATE_DEFAULT, &lv_font_simsun_20);
	lv_style_set_text_letter_space(&style_screen_label3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label3, LV_LABEL_PART_MAIN, &style_screen_label3_main);
	lv_obj_set_pos(ui->screen_label3, 42, 23);
	lv_obj_set_size(ui->screen_label3, 237, 0);
	lv_anim_path_t lv_anim_path_screen_btn4 = {.cb = lv_anim_path_overshoot};

	//Write codes screen_btn4
	ui->screen_btn4 = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_btn4
	static lv_style_t style_screen_btn4_main;
	lv_style_init(&style_screen_btn4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_btn4_main
	lv_style_set_radius(&style_screen_btn4_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_btn4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_btn4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_btn4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btn4_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_btn4_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_btn4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_screen_btn4_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_btn4_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_screen_btn4_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_btn4, LV_BTN_PART_MAIN, &style_screen_btn4_main);
	lv_obj_set_pos(ui->screen_btn4, 220, 395);
	lv_obj_set_size(ui->screen_btn4, 100, 50);

	//Write animation: screen_btn4move in x direction
	lv_anim_t screen_btn4_x;
	lv_anim_init(&screen_btn4_x);
	lv_anim_set_var(&screen_btn4_x, ui->screen_btn4);
	lv_anim_set_time(&screen_btn4_x, 1000);
	lv_anim_set_exec_cb(&screen_btn4_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
	lv_anim_set_values(&screen_btn4_x, lv_obj_get_x(ui->screen_btn4), 110);
	_lv_memcpy_small(&screen_btn4_x.path, &lv_anim_path_screen_btn4, sizeof(lv_anim_path_cb_t));
	lv_anim_start(&screen_btn4_x);
	ui->screen_btn4_label = lv_label_create(ui->screen_btn4, NULL);
	lv_label_set_text(ui->screen_btn4_label, "stress");
	lv_obj_set_style_local_text_color(ui->screen_btn4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_btn4_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);

	//Write codes screen_label5
	ui->screen_label5 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label5, "Copyright 2021 Espressif System");
	lv_label_set_long_mode(ui->screen_label5, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label5, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label5
	static lv_style_t style_screen_label5_main;
	lv_style_init(&style_screen_label5_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label5_main
	lv_style_set_radius(&style_screen_label5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label5_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label5_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_label5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label5, LV_LABEL_PART_MAIN, &style_screen_label5_main);
	lv_obj_set_pos(ui->screen_label5, 10, 465);
	lv_obj_set_size(ui->screen_label5, 301, 0);

	//Init events for screen
	events_init_screen(ui);
}