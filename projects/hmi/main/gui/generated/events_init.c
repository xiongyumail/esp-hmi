/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "lv_examples.h"




void events_init(lv_ui *ui)
{
}

static void screen_btn0event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		lv_obj_clean(lv_scr_act());
		lv_demo_benchmark();
	}
		break;
	default:
		break;
	}
}

static void screen_btn1event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		lv_obj_clean(lv_scr_act());
		lv_demo_music();
	}
		break;
	default:
		break;
	}
}

static void screen_btn2event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		lv_demo_widgets();
	}
		break;
	default:
		break;
	}
}

static void screen_btn4event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		lv_obj_clean(lv_scr_act());
		lv_demo_stress();
	}
		break;
	default:
		break;
	}
}

void events_init_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_btn0, screen_btn0event_handler);
	lv_obj_set_event_cb(ui->screen_btn1, screen_btn1event_handler);
	lv_obj_set_event_cb(ui->screen_btn2, screen_btn2event_handler);
	lv_obj_set_event_cb(ui->screen_btn4, screen_btn4event_handler);
}
