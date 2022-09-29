
#include "pico/stdlib.h"
#include "../globals.h"

#include "hardware/pio.h"

// Here we are writing 32-bit values into the FIFO, one at a time, directly from the CPU. pio_sm_put_blocking is a helper
// method that waits until there is room in the FIFO before pushing your data.
static inline void put_pixel(uint32_t pixel_grb) 
{
    pio_sm_put_blocking(pio0, 0, pixel_grb);
}

static inline uint32_t ugrb_u32(uint8_t g, uint8_t r, uint8_t b) 
{
    return ((uint32_t) (g) << 8) | ((uint32_t) (r) << 16) | ((uint32_t) (b) << 24 );
}

int ws2811_init(PIO pio2811, int sm);
