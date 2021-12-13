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

#pragma once

#include "esp_types.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct st7796_rgb_handle_struct st7796_rgb_handle_t;

typedef struct {
    union {
        struct {
            uint32_t width:      5; /*!< Data bus width (maximum LCD_DATA_MAX_WIDTH) 1: 1bit, 8: 8bit, 16: 16bit */
            uint32_t reserved5:       27;        /*!< CLK clock frequency */
        };
        uint32_t val;
    } bus;
    union {
        struct {
            uint32_t x:      16; /*!< Data bus width (maximum LCD_DATA_MAX_WIDTH) 1: 1bit, 8: 8bit, 16: 16bit */
            uint32_t y:      16; /*!< CLK clock frequency */
        };
        uint32_t val;
    } res;
    union {
        struct {
            uint32_t horizontal:         2;
            uint32_t dis_invert:      1;
            uint32_t dis_bgr:         1; /*!< DMA maximum memory usage, memory must be able to accessed by DMA */
            uint32_t pix_bytes:             3;
            uint32_t reserved7:            25; /*reserved*/
        };
        uint32_t val;
    } ctr;
    union {
        struct {
            uint32_t dc:        16; /*!< CLK output pin */
            uint32_t dc_inv:     1; /*!< CLK output signal inversion */
            uint32_t reserved17: 15; /*reserved*/
        };
        uint32_t val;
    } pin_dc;
    union {
        struct {
            uint32_t rd:        16; /*!< CLK output pin */
            uint32_t rd_inv:     1; /*!< CLK output signal inversion */
            uint32_t reserved17: 15; /*reserved*/
        };
        uint32_t val;
    } pin_rd;
    union {
        struct {
            uint32_t cs:        16; /*!< CLK output pin */
            uint32_t cs_inv:     1; /*!< CLK output signal inversion */
            uint32_t reserved17: 15; /*reserved*/
        };
        uint32_t val;
    } pin_cs;
    union {
        struct {
            uint32_t rst:        16; /*!< CLK output pin */
            uint32_t rst_inv:     1; /*!< CLK output signal inversion */
            uint32_t reserved17: 15; /*reserved*/
        };
        uint32_t val;
    } pin_rst;
    union {
        struct {
            uint32_t bk:        16; /*!< CLK output pin */
            uint32_t bk_inv:     1; /*!< CLK output signal inversion */
            uint32_t reserved17: 15; /*reserved*/
        };
        uint32_t val;
    } pin_bk;
} st7796_rgb_ctrl_t;

typedef struct {
    struct {
        struct {
            void (*run)(st7796_rgb_handle_t *handle);
            void (*stop)(st7796_rgb_handle_t *handle);
        } mst;
        struct {
            void (*run)(st7796_rgb_handle_t *handle);
            void (*stop)(st7796_rgb_handle_t *handle);
        } slv;
    } ctr;

    struct {
        struct {
            void (*write) (st7796_rgb_handle_t *handle, uint8_t *data, size_t len);
        } mst;
        struct {
            void (*start)(st7796_rgb_handle_t *handle, void *arg);
            void (*end)(st7796_rgb_handle_t *handle, void *arg);
        } slv;
    } data;

    struct {
        struct {
            void (*write) (st7796_rgb_handle_t *handle, int pos);
        } mst;
        struct {
            void (*start)(st7796_rgb_handle_t *handle, void *arg);
            void (*end)(st7796_rgb_handle_t *handle, void *arg);
        } slv;
    } fb;
} st7796_rgb_port_t; 

struct st7796_rgb_handle_struct {
    void *self;
    st7796_rgb_ctrl_t *ctrl; // 寄存器
    st7796_rgb_port_t *port; // 驱动器
}; /*!< lcd handle */

esp_err_t st7796_rgb_create(st7796_rgb_handle_t *handle);

esp_err_t st7796_rgb_config(st7796_rgb_handle_t *handle);

esp_err_t st7796_rgb_remove(st7796_rgb_handle_t *handle);


#ifdef __cplusplus
}
#endif