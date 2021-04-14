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

	//Write codes screen_cont8
	ui->screen_cont8 = lv_cont_create(ui->screen, NULL);

	//Write style LV_CONT_PART_MAIN for screen_cont8
	static lv_style_t style_screen_cont8_main;
	lv_style_init(&style_screen_cont8_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_cont8_main
	lv_style_set_radius(&style_screen_cont8_main, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_screen_cont8_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_cont8_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_cont8_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_cont8_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_cont8_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_cont8_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_cont8_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen_cont8_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_cont8_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_cont8_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_cont8_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_cont8, LV_CONT_PART_MAIN, &style_screen_cont8_main);
	lv_obj_set_pos(ui->screen_cont8, 0, 0);
	lv_obj_set_size(ui->screen_cont8, 320, 240);
	lv_obj_set_click(ui->screen_cont8, false);
	lv_cont_set_layout(ui->screen_cont8, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_cont8, LV_FIT_NONE);
	lv_anim_path_t lv_anim_path_screen_doggie_1 = {.cb = lv_anim_path_overshoot};

	//Write codes screen_doggie_1
	ui->screen_doggie_1 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_doggie_1
	static lv_style_t style_screen_doggie_1_main;
	lv_style_init(&style_screen_doggie_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_doggie_1_main
	lv_style_set_image_recolor(&style_screen_doggie_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_doggie_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_doggie_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_doggie_1, LV_IMG_PART_MAIN, &style_screen_doggie_1_main);
	lv_obj_set_pos(ui->screen_doggie_1, 200, 0);
	lv_obj_set_size(ui->screen_doggie_1, 100, 100);
	lv_obj_set_click(ui->screen_doggie_1, true);

	//Write animation: screen_doggie_1move in x direction
	lv_anim_t screen_doggie_1_x;
	lv_anim_init(&screen_doggie_1_x);
	lv_anim_set_var(&screen_doggie_1_x, ui->screen_doggie_1);
	lv_anim_set_time(&screen_doggie_1_x, 2000);
	lv_anim_set_exec_cb(&screen_doggie_1_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
	lv_anim_set_values(&screen_doggie_1_x, lv_obj_get_x(ui->screen_doggie_1), 40);
	_lv_memcpy_small(&screen_doggie_1_x.path, &lv_anim_path_screen_doggie_1, sizeof(lv_anim_path_cb_t));
	lv_anim_start(&screen_doggie_1_x);

	//Write animation: screen_doggie_1move in y direction
	lv_anim_t screen_doggie_1_y;
	lv_anim_init(&screen_doggie_1_y);
	lv_anim_set_var(&screen_doggie_1_y, ui->screen_doggie_1);
	lv_anim_set_time(&screen_doggie_1_y, 2000);
	lv_anim_set_exec_cb(&screen_doggie_1_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
	lv_anim_set_values(&screen_doggie_1_y, lv_obj_get_y(ui->screen_doggie_1), 130);
	_lv_memcpy_small(&screen_doggie_1_y.path, &lv_anim_path_screen_doggie_1, sizeof(lv_anim_path_cb_t));
	lv_anim_start(&screen_doggie_1_y);

	lv_img_set_src(ui->screen_doggie_1,&_doggie_1_alpha_100x100);
	lv_img_set_pivot(ui->screen_doggie_1, 0,0);
	lv_img_set_angle(ui->screen_doggie_1, 0);

	//Write codes screen_clock_lable
	ui->screen_clock_lable = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_clock_lable, "12:10");
	lv_label_set_long_mode(ui->screen_clock_lable, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_clock_lable, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_clock_lable
	static lv_style_t style_screen_clock_lable_main;
	lv_style_init(&style_screen_clock_lable_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_lable_main
	lv_style_set_radius(&style_screen_clock_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_clock_lable_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_clock_lable_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_clock_lable_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_clock_lable_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_clock_lable_main, LV_STATE_DEFAULT, &lv_font_Ni7seg_48);
	lv_style_set_text_letter_space(&style_screen_clock_lable_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_screen_clock_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_clock_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_clock_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_clock_lable_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_clock_lable, LV_LABEL_PART_MAIN, &style_screen_clock_lable_main);
	lv_obj_set_pos(ui->screen_clock_lable, 5, 60);
	lv_obj_set_size(ui->screen_clock_lable, 200, 0);

	//Write codes screen_header
	ui->screen_header = lv_cont_create(ui->screen, NULL);

	//Write style LV_CONT_PART_MAIN for screen_header
	static lv_style_t style_screen_header_main;
	lv_style_init(&style_screen_header_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_header_main
	lv_style_set_radius(&style_screen_header_main, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_screen_header_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_header_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_header_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_header_main, LV_STATE_DEFAULT, 128);
	lv_style_set_border_color(&style_screen_header_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_header_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_header_main, LV_STATE_DEFAULT, 128);
	lv_style_set_pad_left(&style_screen_header_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_header_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_header_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_header_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_header, LV_CONT_PART_MAIN, &style_screen_header_main);
	lv_obj_set_pos(ui->screen_header, 0, 0);
	lv_obj_set_size(ui->screen_header, 320, 30);
	lv_obj_set_click(ui->screen_header, false);
	lv_cont_set_layout(ui->screen_header, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_header, LV_FIT_NONE);

	//Write codes screen_heade_power
	ui->screen_heade_power = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_heade_power, "P");
	lv_label_set_long_mode(ui->screen_heade_power, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_heade_power, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_heade_power
	static lv_style_t style_screen_heade_power_main;
	lv_style_init(&style_screen_heade_power_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_heade_power_main
	lv_style_set_radius(&style_screen_heade_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_heade_power_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_heade_power_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_heade_power_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_heade_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_heade_power_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_heade_power_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_heade_power_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_heade_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_heade_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_heade_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_heade_power_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_heade_power, LV_LABEL_PART_MAIN, &style_screen_heade_power_main);
	lv_obj_set_pos(ui->screen_heade_power, 6, 8);
	lv_obj_set_size(ui->screen_heade_power, 30, 0);

	//Write codes screen_heade_net
	ui->screen_heade_net = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_heade_net, "W");
	lv_label_set_long_mode(ui->screen_heade_net, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_heade_net, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_heade_net
	static lv_style_t style_screen_heade_net_main;
	lv_style_init(&style_screen_heade_net_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_heade_net_main
	lv_style_set_radius(&style_screen_heade_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_heade_net_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_heade_net_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_heade_net_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_heade_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_heade_net_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_heade_net_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_heade_net_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_heade_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_heade_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_heade_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_heade_net_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_heade_net, LV_LABEL_PART_MAIN, &style_screen_heade_net_main);
	lv_obj_set_pos(ui->screen_heade_net, 46, 8);
	lv_obj_set_size(ui->screen_heade_net, 30, 0);

	//Write codes screen_heade_state
	ui->screen_heade_state = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_heade_state, "S");
	lv_label_set_long_mode(ui->screen_heade_state, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_heade_state, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_heade_state
	static lv_style_t style_screen_heade_state_main;
	lv_style_init(&style_screen_heade_state_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_heade_state_main
	lv_style_set_radius(&style_screen_heade_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_heade_state_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_heade_state_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_heade_state_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_heade_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_heade_state_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_heade_state_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_heade_state_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_heade_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_heade_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_heade_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_heade_state_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_heade_state, LV_LABEL_PART_MAIN, &style_screen_heade_state_main);
	lv_obj_set_pos(ui->screen_heade_state, 284, 8);
	lv_obj_set_size(ui->screen_heade_state, 30, 0);

	//Write codes screen_clock_s_lable
	ui->screen_clock_s_lable = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_clock_s_lable, "20");
	lv_label_set_long_mode(ui->screen_clock_s_lable, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_clock_s_lable, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_clock_s_lable
	static lv_style_t style_screen_clock_s_lable_main;
	lv_style_init(&style_screen_clock_s_lable_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_s_lable_main
	lv_style_set_radius(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, &lv_font_Ni7seg_22);
	lv_style_set_text_letter_space(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_clock_s_lable_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_clock_s_lable, LV_LABEL_PART_MAIN, &style_screen_clock_s_lable_main);
	lv_obj_set_pos(ui->screen_clock_s_lable, 200, 82);
	lv_obj_set_size(ui->screen_clock_s_lable, 40, 0);

	//Write codes screen_date
	ui->screen_date = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_date, "4月14");
	lv_label_set_long_mode(ui->screen_date, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_date, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_date
	static lv_style_t style_screen_date_main;
	lv_style_init(&style_screen_date_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_main
	lv_style_set_radius(&style_screen_date_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_date_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_date_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_date_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_date_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_date_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_date_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_date_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_date_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_date, LV_LABEL_PART_MAIN, &style_screen_date_main);
	lv_obj_set_pos(ui->screen_date, 200, 196);
	lv_obj_set_size(ui->screen_date, 60, 0);

	//Write codes screen_week
	ui->screen_week = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_week, "周三");
	lv_label_set_long_mode(ui->screen_week, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_week, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_week
	static lv_style_t style_screen_week_main;
	lv_style_init(&style_screen_week_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_week_main
	lv_style_set_radius(&style_screen_week_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_week_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_week_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_week_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_week_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_week_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_week_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_week_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_week_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_week_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_week_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_week_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_week, LV_LABEL_PART_MAIN, &style_screen_week_main);
	lv_obj_set_pos(ui->screen_week, 195, 161);
	lv_obj_set_size(ui->screen_week, 60, 0);

	//Write codes screen_line10
	ui->screen_line10 = lv_line_create(ui->screen, NULL);

	//Write style LV_LINE_PART_MAIN for screen_line10
	static lv_style_t style_screen_line10_main;
	lv_style_init(&style_screen_line10_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_line10_main
	lv_style_set_line_color(&style_screen_line10_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_screen_line10_main, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen_line10, LV_LINE_PART_MAIN, &style_screen_line10_main);
	lv_obj_set_pos(ui->screen_line10, 250, 40);
	lv_obj_set_size(ui->screen_line10, 1, 90);
	static lv_point_t screen_line10[] ={{0,0},{0,90}};
	lv_line_set_points(ui->screen_line10,screen_line10,2);

	//Write codes screen_line11
	ui->screen_line11 = lv_line_create(ui->screen, NULL);

	//Write style LV_LINE_PART_MAIN for screen_line11
	static lv_style_t style_screen_line11_main;
	lv_style_init(&style_screen_line11_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_line11_main
	lv_style_set_line_color(&style_screen_line11_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_screen_line11_main, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen_line11, LV_LINE_PART_MAIN, &style_screen_line11_main);
	lv_obj_set_pos(ui->screen_line11, 10, 130);
	lv_obj_set_size(ui->screen_line11, 240, 1);
	static lv_point_t screen_line11[] ={{0,0},{240,0}};
	lv_line_set_points(ui->screen_line11,screen_line11,2);

	//Write codes screen_line10_12
	ui->screen_line10_12 = lv_line_create(ui->screen, NULL);

	//Write style LV_LINE_PART_MAIN for screen_line10_12
	static lv_style_t style_screen_line10_12_main;
	lv_style_init(&style_screen_line10_12_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_line10_12_main
	lv_style_set_line_color(&style_screen_line10_12_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_screen_line10_12_main, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen_line10_12, LV_LINE_PART_MAIN, &style_screen_line10_12_main);
	lv_obj_set_pos(ui->screen_line10_12, 180, 130);
	lv_obj_set_size(ui->screen_line10_12, 1, 100);
	static lv_point_t screen_line10_12[] ={{0,0},{0,100}};
	lv_line_set_points(ui->screen_line10_12,screen_line10_12,2);

	//Write codes screen_line13
	ui->screen_line13 = lv_line_create(ui->screen, NULL);

	//Write style LV_LINE_PART_MAIN for screen_line13
	static lv_style_t style_screen_line13_main;
	lv_style_init(&style_screen_line13_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_line13_main
	lv_style_set_line_color(&style_screen_line13_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_screen_line13_main, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen_line13, LV_LINE_PART_MAIN, &style_screen_line13_main);
	lv_obj_set_pos(ui->screen_line13, 250, 130);
	lv_obj_set_size(ui->screen_line13, 70, 110);
	static lv_point_t screen_line13[] ={{0,0},{60,100}};
	lv_line_set_points(ui->screen_line13,screen_line13,2);

	//Write codes screen_label14
	ui->screen_label14 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label14, "晴天");
	lv_label_set_long_mode(ui->screen_label14, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label14, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label14
	static lv_style_t style_screen_label14_main;
	lv_style_init(&style_screen_label14_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label14_main
	lv_style_set_radius(&style_screen_label14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label14_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label14_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label14_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label14_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label14_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_label14_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label14_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label14_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label14, LV_LABEL_PART_MAIN, &style_screen_label14_main);
	lv_obj_set_pos(ui->screen_label14, 261, 96);
	lv_obj_set_size(ui->screen_label14, 50, 0);

	//Write codes screen_label15
	ui->screen_label15 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label15, "20'C");
	lv_label_set_long_mode(ui->screen_label15, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label15, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label15
	static lv_style_t style_screen_label15_main;
	lv_style_init(&style_screen_label15_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label15_main
	lv_style_set_radius(&style_screen_label15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label15_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label15_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label15_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label15_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label15_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_label15_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label15_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label15_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label15, LV_LABEL_PART_MAIN, &style_screen_label15_main);
	lv_obj_set_pos(ui->screen_label15, 260, 118);
	lv_obj_set_size(ui->screen_label15, 50, 0);

	//Write codes screen_img16
	ui->screen_img16 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img16
	static lv_style_t style_screen_img16_main;
	lv_style_init(&style_screen_img16_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img16_main
	lv_style_set_image_recolor(&style_screen_img16_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img16_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img16_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img16, LV_IMG_PART_MAIN, &style_screen_img16_main);
	lv_obj_set_pos(ui->screen_img16, 252, 32);
	lv_obj_set_size(ui->screen_img16, 64, 64);
	lv_obj_set_click(ui->screen_img16, true);
	lv_img_set_src(ui->screen_img16,&_sun_alpha_64x64);
	lv_img_set_pivot(ui->screen_img16, 0,0);
	lv_img_set_angle(ui->screen_img16, 0);
}