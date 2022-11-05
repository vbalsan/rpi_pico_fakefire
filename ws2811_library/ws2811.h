
#include "pico/stdlib.h"
#include "../globals.h"

#include "hardware/pio.h"

int ws2811sm;

void ws2811_init(PIO pio2811, int sm, uint8_t ws2811LedsPin);
void Leds_init(PIO pio2811, uint8_t ws2811LedsPin);

// Here we are writing 32-bit values into the FIFO, one at a time, directly from the CPU. pio_sm_put_blocking is a helper
// method that waits until there is room in the FIFO before pushing your data.
static inline void put_pixel(uint32_t pixel_grb) 
{
    pio_sm_put_blocking(WS2811_PIO, ws2811sm, pixel_grb);
}

static inline uint32_t ugrb_u32(uint8_t g, uint8_t r, uint8_t b) 
{
    return ((uint32_t) (g) << 8) | ((uint32_t) (r) << 16) | ((uint32_t) (b) << 24 );
}




