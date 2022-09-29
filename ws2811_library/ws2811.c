
#include "ws2811.h"
#include "hardware/pio.h"
#include "ws2811.pio.h"



int ws2811_init(PIO pio2811, int sm)
{
    uint offset = pio_add_program(pio2811, &ws2811_program);
    ws2811_program_init(pio2811, sm, offset, WS2811_PIN, 800000);
    return offset;
}