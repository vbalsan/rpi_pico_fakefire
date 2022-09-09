/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "values.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2811.pio.h"

#define IS_RGBW false
#define NUM_PIXELS 50

#ifdef PICO_DEFAULT_WS2811_PIN
#define WS2811_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2811 pin defined
#define WS2811_PIN 2
#endif


// Here we are writing 32-bit values into the FIFO, one at a time, directly from the CPU. pio_sm_put_blocking is a helper
// method that waits until there is room in the FIFO before pushing your data.
static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb);
}

static inline uint32_t ugrb_u32(uint8_t g, uint8_t r, uint8_t b) {
    return ((uint32_t) (g) << 8) | ((uint32_t) (r) << 16) | ((uint32_t) (b) << 24 );
}



int main() {

    stdio_init_all();

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2811_program);


    ws2811_program_init(pio, sm, offset, WS2811_PIN, 800000);

    uint8_t g = 25;
    uint8_t r = 255;    
    uint8_t b = 0;

    uint8_t gidx = 0;
    uint8_t ridx = 0;    
    uint8_t bidx = 0;

    uint32_t pixel;

    while (1) 
    {
        pixel = ugrb_u32( g,  r,  b);

        for (int i = 0; i < NUM_PIXELS -1; ++i) 
        {            
           //put_pixel(pixel);
           put_pixel(0);
        }
        put_pixel(pixel);

        sleep_ms(100);
        
        //g = green_arr[++gidx];
        r = red_arr[++ridx];
        g = (uint8_t)(r/10u);
        //b = blu_arr[++bidx];
        b = (uint8_t)(r/50u);

        /*
        g = 0;
        r = 255;
        b = 0;
        pixel = ugrb_u32( g,  r,  b);

        for (int i = 0; i < NUM_PIXELS; ++i) 
        {            
           put_pixel(pixel);
        }
        sleep_ms(2000);


        g = 0;
        r = 0;
        b = 255;
        pixel = ugrb_u32( g,  r,  b);

        for (int i = 0; i < NUM_PIXELS; ++i) 
        {            
           put_pixel(pixel);
        }
        sleep_ms(2000);
        */

    }
}
