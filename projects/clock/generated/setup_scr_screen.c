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

	//Write codes screen_main_cont
	ui->screen_main_cont = lv_cont_create(ui->screen, NULL);

	//Write style LV_CONT_PART_MAIN for screen_main_cont
	static lv_style_t style_screen_main_cont_main;
	lv_style_init(&style_screen_main_cont_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_cont_main
	lv_style_set_radius(&style_screen_main_cont_main, LV_STATE_DEFAULT, 4);
	lv_style_set_bg_color(&style_screen_main_cont_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_main_cont_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_main_cont_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_cont_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_main_cont_main, LV_STATE_DEFAULT, lv_color_make(0x99, 0x99, 0x99));
	lv_style_set_border_width(&style_screen_main_cont_main, LV_STATE_DEFAULT, 1);
	lv_style_set_border_opa(&style_screen_main_cont_main, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen_main_cont_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_main_cont_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_main_cont_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_main_cont_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_main_cont, LV_CONT_PART_MAIN, &style_screen_main_cont_main);
	lv_obj_set_pos(ui->screen_main_cont, 0, 0);
	lv_obj_set_size(ui->screen_main_cont, 320, 240);
	lv_obj_set_click(ui->screen_main_cont, false);
	lv_cont_set_layout(ui->screen_main_cont, LV_LAYOUT_OFF);
	lv_cont_set_fit(ui->screen_main_cont, LV_FIT_NONE);

	//Write codes screen_image
	ui->screen_image = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_image
	static lv_style_t style_screen_image_main;
	lv_style_init(&style_screen_image_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_image_main
	lv_style_set_image_recolor(&style_screen_image_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_image_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_image_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_image, LV_IMG_PART_MAIN, &style_screen_image_main);
	lv_obj_set_pos(ui->screen_image, 40, 130);
	lv_obj_set_size(ui->screen_image, 100, 100);
	lv_obj_set_click(ui->screen_image, true);
	lv_img_set_src(ui->screen_image,&_doggie_1_alpha_100x100);
	lv_img_set_pivot(ui->screen_image, 0,0);
	lv_img_set_angle(ui->screen_image, 0);

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

	//Write codes screen_power
	ui->screen_power = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_power, "P");
	lv_label_set_long_mode(ui->screen_power, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_power, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_power
	static lv_style_t style_screen_power_main;
	lv_style_init(&style_screen_power_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_power_main
	lv_style_set_radius(&style_screen_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_power_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_power_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_power_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_power_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_power_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_power_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_power_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_power_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_power, LV_LABEL_PART_MAIN, &style_screen_power_main);
	lv_obj_set_pos(ui->screen_power, 6, 8);
	lv_obj_set_size(ui->screen_power, 30, 0);

	//Write codes screen_net
	ui->screen_net = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_net, "W");
	lv_label_set_long_mode(ui->screen_net, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_net, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_net
	static lv_style_t style_screen_net_main;
	lv_style_init(&style_screen_net_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_net_main
	lv_style_set_radius(&style_screen_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_net_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_net_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_net_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_net_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_net_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_net_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_net_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_net_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_net, LV_LABEL_PART_MAIN, &style_screen_net_main);
	lv_obj_set_pos(ui->screen_net, 46, 8);
	lv_obj_set_size(ui->screen_net, 30, 0);

	//Write codes screen_state
	ui->screen_state = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_state, "S");
	lv_label_set_long_mode(ui->screen_state, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_state, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_state
	static lv_style_t style_screen_state_main;
	lv_style_init(&style_screen_state_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_state_main
	lv_style_set_radius(&style_screen_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_state_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_state_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_state_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_state_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_state_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_state_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_state_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_state_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_state, LV_LABEL_PART_MAIN, &style_screen_state_main);
	lv_obj_set_pos(ui->screen_state, 284, 8);
	lv_obj_set_size(ui->screen_state, 30, 0);

	//Write codes screen_clock
	ui->screen_clock = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_clock, "12:10");
	lv_label_set_long_mode(ui->screen_clock, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_clock, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_clock
	static lv_style_t style_screen_clock_main;
	lv_style_init(&style_screen_clock_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_main
	lv_style_set_radius(&style_screen_clock_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_clock_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_clock_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_clock_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_clock_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_clock_main, LV_STATE_DEFAULT, &lv_font_Ni7seg_48);
	lv_style_set_text_letter_space(&style_screen_clock_main, LV_STATE_DEFAULT, 4);
	lv_style_set_pad_left(&style_screen_clock_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_clock_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_clock_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_clock_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_clock, LV_LABEL_PART_MAIN, &style_screen_clock_main);
	lv_obj_set_pos(ui->screen_clock, 5, 60);
	lv_obj_set_size(ui->screen_clock, 200, 0);

	//Write codes screen_clock_s
	ui->screen_clock_s = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_clock_s, "20");
	lv_label_set_long_mode(ui->screen_clock_s, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_clock_s, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_clock_s
	static lv_style_t style_screen_clock_s_main;
	lv_style_init(&style_screen_clock_s_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_s_main
	lv_style_set_radius(&style_screen_clock_s_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_clock_s_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_clock_s_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_clock_s_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_s_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_clock_s_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_clock_s_main, LV_STATE_DEFAULT, &lv_font_Ni7seg_22);
	lv_style_set_text_letter_space(&style_screen_clock_s_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_clock_s_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_clock_s_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_clock_s_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_clock_s_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_clock_s, LV_LABEL_PART_MAIN, &style_screen_clock_s_main);
	lv_obj_set_pos(ui->screen_clock_s, 200, 82);
	lv_obj_set_size(ui->screen_clock_s, 40, 0);

	//Write codes screen_date_y
	ui->screen_date_y = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_date_y, "2021年");
	lv_label_set_long_mode(ui->screen_date_y, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_date_y, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_date_y
	static lv_style_t style_screen_date_y_main;
	lv_style_init(&style_screen_date_y_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_y_main
	lv_style_set_radius(&style_screen_date_y_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_date_y_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_y_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_y_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_y_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_date_y_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_date_y_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_date_y_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_date_y_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_date_y_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_date_y_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_date_y_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_date_y, LV_LABEL_PART_MAIN, &style_screen_date_y_main);
	lv_obj_set_pos(ui->screen_date_y, 180, 150);
	lv_obj_set_size(ui->screen_date_y, 100, 0);

	//Write codes screen_date_md
	ui->screen_date_md = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_date_md, "04月14日");
	lv_label_set_long_mode(ui->screen_date_md, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_date_md, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_date_md
	static lv_style_t style_screen_date_md_main;
	lv_style_init(&style_screen_date_md_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_md_main
	lv_style_set_radius(&style_screen_date_md_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_date_md_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_md_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_md_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_md_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_date_md_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_date_md_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_date_md_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_date_md_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_date_md_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_date_md_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_date_md_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_date_md, LV_LABEL_PART_MAIN, &style_screen_date_md_main);
	lv_obj_set_pos(ui->screen_date_md, 180, 180);
	lv_obj_set_size(ui->screen_date_md, 100, 0);

	//Write codes screen_date_w
	ui->screen_date_w = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_date_w, "周一二三四五六七");
	lv_label_set_long_mode(ui->screen_date_w, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_date_w, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_date_w
	static lv_style_t style_screen_date_w_main;
	lv_style_init(&style_screen_date_w_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_date_w_main
	lv_style_set_radius(&style_screen_date_w_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_date_w_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_date_w_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_date_w_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_date_w_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_date_w_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_date_w_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_date_w_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_date_w_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_date_w_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_date_w_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_date_w_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_date_w, LV_LABEL_PART_MAIN, &style_screen_date_w_main);
	lv_obj_set_pos(ui->screen_date_w, 180, 205);
	lv_obj_set_size(ui->screen_date_w, 100, 0);

	//Write codes screen_weather_image
	ui->screen_weather_image = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_weather_image
	static lv_style_t style_screen_weather_image_main;
	lv_style_init(&style_screen_weather_image_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_weather_image_main
	lv_style_set_image_recolor(&style_screen_weather_image_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_weather_image_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_weather_image_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_weather_image, LV_IMG_PART_MAIN, &style_screen_weather_image_main);
	lv_obj_set_pos(ui->screen_weather_image, 252, 32);
	lv_obj_set_size(ui->screen_weather_image, 64, 64);
	lv_obj_set_click(ui->screen_weather_image, true);
	lv_img_set_src(ui->screen_weather_image,&_sun_alpha_64x64);
	lv_img_set_pivot(ui->screen_weather_image, 0,0);
	lv_img_set_angle(ui->screen_weather_image, 0);

	//Write codes screen_weather
	ui->screen_weather = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_weather, "晴雨阴天");
	lv_label_set_long_mode(ui->screen_weather, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_weather, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_weather
	static lv_style_t style_screen_weather_main;
	lv_style_init(&style_screen_weather_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_weather_main
	lv_style_set_radius(&style_screen_weather_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_weather_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_weather_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_weather_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_weather_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_weather_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_weather_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_weather_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_weather_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_weather_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_weather_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_weather_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_weather, LV_LABEL_PART_MAIN, &style_screen_weather_main);
	lv_obj_set_pos(ui->screen_weather, 261, 96);
	lv_obj_set_size(ui->screen_weather, 50, 0);

	//Write codes screen_temp
	ui->screen_temp = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_temp, "20'C");
	lv_label_set_long_mode(ui->screen_temp, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_temp, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_temp
	static lv_style_t style_screen_temp_main;
	lv_style_init(&style_screen_temp_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_temp_main
	lv_style_set_radius(&style_screen_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_temp_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_temp_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_temp_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_temp_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_temp_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_temp_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_temp_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_temp, LV_LABEL_PART_MAIN, &style_screen_temp_main);
	lv_obj_set_pos(ui->screen_temp, 260, 118);
	lv_obj_set_size(ui->screen_temp, 50, 0);

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

	//Write codes screen_line11_17
	ui->screen_line11_17 = lv_line_create(ui->screen, NULL);

	//Write style LV_LINE_PART_MAIN for screen_line11_17
	static lv_style_t style_screen_line11_17_main;
	lv_style_init(&style_screen_line11_17_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_line11_17_main
	lv_style_set_line_color(&style_screen_line11_17_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_screen_line11_17_main, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen_line11_17, LV_LINE_PART_MAIN, &style_screen_line11_17_main);
	lv_obj_set_pos(ui->screen_line11_17, 250, 130);
	lv_obj_set_size(ui->screen_line11_17, 60, 60);
	static lv_point_t screen_line11_17[] ={{0,0},{30,60}};
	lv_line_set_points(ui->screen_line11_17,screen_line11_17,2);

	//Write codes screen_line10_18
	ui->screen_line10_18 = lv_line_create(ui->screen, NULL);

	//Write style LV_LINE_PART_MAIN for screen_line10_18
	static lv_style_t style_screen_line10_18_main;
	lv_style_init(&style_screen_line10_18_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_line10_18_main
	lv_style_set_line_color(&style_screen_line10_18_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_line_width(&style_screen_line10_18_main, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->screen_line10_18, LV_LINE_PART_MAIN, &style_screen_line10_18_main);
	lv_obj_set_pos(ui->screen_line10_18, 280, 190);
	lv_obj_set_size(ui->screen_line10_18, 1, 40);
	static lv_point_t screen_line10_18[] ={{0,0},{0,40}};
	lv_line_set_points(ui->screen_line10_18,screen_line10_18,2);
}