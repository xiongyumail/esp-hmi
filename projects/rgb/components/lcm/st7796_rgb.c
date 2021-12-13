// Copyright 2010-2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "st7796_rgb.h"

static const char *TAG = "lcm";

#define ST7796_RGB_DEFAULT_CTRL() (st7796_rgb_ctrl_t) { \
    .bus = {.width = 8}, \
    .res = {.x = 320, .y = 480}, \
    .ctr = {.horizontal = 2, .dis_invert = true, .dis_bgr = false, .pix_bytes = 2} \
}

typedef struct st7796_rgb_self_struct st7796_rgb_self_t;

struct st7796_rgb_self_struct{
    st7796_rgb_handle_t *handle;
    st7796_rgb_self_t *next;
};

static void inline st7796_rgb_set_level(st7796_rgb_self_t *self, int8_t io_num, uint8_t state, bool invert)
{
    if (io_num < 0) {
        return;
    }
    gpio_set_level(io_num, invert ? !state : state);
}

static void st7796_rgb_delay_ms(st7796_rgb_self_t *self, uint32_t time)
{
    vTaskDelay(time / portTICK_RATE_MS);
}

static void st7796_rgb_write_cmd(st7796_rgb_self_t *self, uint8_t cmd, uint32_t len, ...)
{
    st7796_rgb_ctrl_t *ctrl = self->handle->ctrl;
    st7796_rgb_port_t *port = self->handle->port;

    if (len > 32) {
        return;
    }
    va_list arg_ptr; 
    uint8_t command_param[32] = { 0 };
    va_start(arg_ptr, len);
    for (int x = 0; x < len; x++) {
        command_param[x] = va_arg(arg_ptr, int);
    }
    va_end(arg_ptr); 

    st7796_rgb_set_level(self, ctrl->pin_dc.dc, 0, ctrl->pin_dc.dc_inv);
    port->data.mst.write(self->handle, &cmd, 1);
    st7796_rgb_set_level(self, ctrl->pin_dc.dc, 1, ctrl->pin_dc.dc_inv);
    if (len > 0) {
        port->data.mst.write(self->handle, command_param, len);
    }
}

static void st7796_rgb_write_data(st7796_rgb_self_t *self, uint8_t *data, size_t len)
{
    st7796_rgb_ctrl_t *ctrl = self->handle->ctrl;
    st7796_rgb_port_t *port = self->handle->port;
    
    if (len <= 0) {
        return;
    }
    st7796_rgb_set_level(self, ctrl->pin_dc.dc, 1, ctrl->pin_dc.dc_inv);
    port->data.mst.write(self->handle, data, len);
}

static void st7796_rgb_rst(st7796_rgb_self_t *self)
{
    st7796_rgb_ctrl_t *ctrl = self->handle->ctrl;

    st7796_rgb_set_level(self, ctrl->pin_rst.rst, 0, ctrl->pin_rst.rst_inv);
    st7796_rgb_delay_ms(self, 100);
    st7796_rgb_set_level(self, ctrl->pin_rst.rst, 1, ctrl->pin_rst.rst_inv);
    st7796_rgb_delay_ms(self, 100);
}

static void st7796_rgb_reg_config(st7796_rgb_self_t *self)
{
    st7796_rgb_ctrl_t *ctrl = self->handle->ctrl;

    st7796_rgb_write_cmd(self, 0x11, 0);         //Sleep Out
    st7796_rgb_delay_ms(self, 200);
    st7796_rgb_write_cmd(self, 0xf0, 1, 0xc3); //enable command 2 part 1        
    st7796_rgb_write_cmd(self, 0xf0, 1, 0x96); //enable command 2 part 2 
    //内存数据访问控制
    switch (ctrl->ctr.horizontal) {
        case 0: {
            st7796_rgb_write_cmd(self, 0x36, 1, 0x28);
        }
        break;

        case 1: {
            st7796_rgb_write_cmd(self, 0x36, 1, 0xA8);
        }
        break;

        case 2: {
            st7796_rgb_write_cmd(self, 0x36, 1, 0x48);
        }
        break;

        case 3: {
            st7796_rgb_write_cmd(self, 0x36, 1, 0xC8);
        }
        break;

        default: {
            st7796_rgb_write_cmd(self, 0x36, 1, 0x28);
        }
        break;
    }
    
    st7796_rgb_write_cmd(self, 0x3a, 1, 0x55);         //16bit pixel
    
    st7796_rgb_write_cmd(self, 0xb4, 1, 0x01);
    st7796_rgb_write_cmd(self, 0xb7, 1, 0xc6);
    st7796_rgb_write_cmd(self, 0xe8, 8, 0x40, 0x8a, 0x00, 0x00, 0x29, 0x19, 0xa5, 0x33);
    st7796_rgb_write_cmd(self, 0xc1, 5, 0x06, 0xc2, 0xa7, 0xc5, 0x18);
    st7796_rgb_write_cmd(self, 0xe0, 14, 0xf0, 0x09, 0x0b, 0x06, 0x04, 0x15, 0x2f, 0x54, 0x42, 0x3c, 0x17, 0x14, 0x18, 0x1b);
    
    //Negative Voltage Gamma Coltrol
    st7796_rgb_write_cmd(self, 0xe1, 14, 0xf0, 0x09, 0x0b, 0x06, 0x04, 0x03, 0x2d, 0x43, 0x42, 0x3b, 0x16, 0x14, 0x17, 0x1b);
    
    st7796_rgb_write_cmd(self, 0xf0, 1, 0x3c);
    st7796_rgb_write_cmd(self, 0xf0, 1, 0x69);

    st7796_rgb_write_cmd(self, 0x13, 0); 
    st7796_rgb_write_cmd(self, 0x38, 0); //Normal mode
    st7796_rgb_delay_ms(self, 120);
    st7796_rgb_write_cmd(self, 0x29, 0); //Display ON
}

static void st7796_rgb_set_index(st7796_rgb_self_t *self, uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{
    st7796_rgb_write_cmd(self, 0x2a, 4, (x_start >> 8) & 0xFF, x_start & 0xFF, (x_end >> 8) & 0xFF, x_end & 0xFF); // CASET (2Ah): Column Address Set 
    st7796_rgb_write_cmd(self, 0x2b, 4, (y_start >> 8) & 0xFF, y_start & 0xFF, (y_end >> 8) & 0xFF, y_end & 0xFF); // RASET (2Bh): Row Address Set
    st7796_rgb_write_cmd(self, 0x2c, 0);    // RAMWR (2Ch): Memory Write 
}

static void st7796_rgb_run(st7796_rgb_handle_t *handle)
{
    st7796_rgb_self_t *self = handle->self;
    st7796_rgb_ctrl_t *ctrl = handle->ctrl;
    st7796_rgb_port_t *port = handle->port;

    if (port->data.mst.write == NULL || \
        port->fb.mst.write == NULL) {
        ESP_LOGE(TAG, "st7796_rgb run fail!");
        st7796_rgb_remove(handle);
        return ESP_FAIL;
    }
    port->ctr.mst.run(self->handle);
    //Initialize non-matrix GPIOs
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask  = ((int8_t)ctrl->pin_dc.dc < 0) ? 0ULL : (1ULL << (int8_t)ctrl->pin_dc.dc);
    io_conf.pin_bit_mask |= ((int8_t)ctrl->pin_rd.rd < 0) ? 0ULL : (1ULL << (int8_t)ctrl->pin_rd.rd);
    io_conf.pin_bit_mask |= ((int8_t)ctrl->pin_rst.rst < 0) ? 0ULL : (1ULL << (int8_t)ctrl->pin_rst.rst);
    io_conf.pin_bit_mask |= ((int8_t)ctrl->pin_bk.bk < 0) ? 0ULL : (1ULL << (int8_t)ctrl->pin_bk.bk);
    io_conf.pin_bit_mask |= ((int8_t)ctrl->pin_cs.cs < 0) ? 0ULL : (1ULL << (int8_t)ctrl->pin_cs.cs);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    st7796_rgb_set_level(self, ctrl->pin_rd.rd, 1, ctrl->pin_rd.rd_inv);
    st7796_rgb_set_level(self, ctrl->pin_cs.cs, 1, ctrl->pin_cs.cs_inv);
    st7796_rgb_rst(self);//st7796_rgb_rst before LCD Init.
    st7796_rgb_delay_ms(self, 100);
    st7796_rgb_set_level(self, ctrl->pin_cs.cs, 0, ctrl->pin_cs.cs_inv);
    st7796_rgb_reg_config(self);
    st7796_rgb_set_level(self, ctrl->pin_bk.bk, 1, ctrl->pin_bk.bk_inv);
    port->fb.mst.write(self->handle, 0);
    return ESP_OK;
}

#include "esp_wifi.h"

static void st7796_rgb_fb_start_callback(st7796_rgb_handle_t *handle)
{
    st7796_rgb_self_t *self = handle->self;
    st7796_rgb_ctrl_t *ctrl = handle->ctrl;

    static uint32_t ticks_now = 0, ticks_last = 0;
    struct timeval now;  

    gettimeofday(&now, NULL);
    ticks_now = now.tv_sec * 1000 + now.tv_usec / 1000;
    if (ticks_now - ticks_last > 0) {
        ESP_LOGI(TAG, "fps: %.2f\n", 1000.0 / (int)(ticks_now - ticks_last));
    }
    ticks_last = ticks_now;
    st7796_rgb_set_index(self, 0, 0, ctrl->res.x - 1, ctrl->res.y - 1);
}

esp_err_t st7796_rgb_create(st7796_rgb_handle_t *handle)
{
    if (handle == NULL) {
        ESP_LOGE(TAG, "arg error\n");
        return ESP_ERR_INVALID_ARG;
    }
    handle->self = (void *)heap_caps_calloc(1, sizeof(st7796_rgb_self_t), MALLOC_CAP_DEFAULT);
    handle->ctrl = (st7796_rgb_ctrl_t *)heap_caps_calloc(1, sizeof(st7796_rgb_ctrl_t), MALLOC_CAP_DEFAULT);
    handle->port = (st7796_rgb_port_t *)heap_caps_calloc(1, sizeof(st7796_rgb_port_t), MALLOC_CAP_DEFAULT);
    if (handle->self == NULL || \
        handle->ctrl == NULL || \
        handle->port == NULL) {
        ESP_LOGE(TAG, "st7796_rgb create fail!");
        st7796_rgb_remove(handle);
        return ESP_FAIL;
    }

    memcpy(handle->ctrl, &ST7796_RGB_DEFAULT_CTRL(), sizeof(st7796_rgb_ctrl_t));

    return ESP_OK;
}

esp_err_t st7796_rgb_config(st7796_rgb_handle_t *handle)
{
    st7796_rgb_self_t *self = handle->self;
    st7796_rgb_port_t *port = handle->port;

    self->handle = handle;

    port->ctr.slv.run = st7796_rgb_run;
    port->data.slv.start = NULL;
    port->data.slv.end = NULL;
    port->fb.slv.start = st7796_rgb_fb_start_callback;
    port->fb.slv.end = NULL;

    return ESP_OK;
}

esp_err_t st7796_rgb_remove(st7796_rgb_handle_t *handle)
{
    if (handle == NULL) {
        ESP_LOGE(TAG, "arg error\n");
        return ESP_ERR_INVALID_ARG;
    }

    st7796_rgb_self_t *self = handle->self;
    
    free(self);
    self = NULL;
    return ESP_OK;
}
