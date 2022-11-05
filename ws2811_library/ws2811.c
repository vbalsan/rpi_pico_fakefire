
#include "ws2811.h"
#include "hardware/pio.h"
#include "ws2811.pio.h"


void Leds_init(PIO pio2811, uint8_t ws2811LedsPin)
{
    //PIO pio2811 = pioLeds;
    // claim an unused state machine on this PIO
    ws2811sm = pio_claim_unused_sm(pio2811, true);
    if (ws2811sm == -1) {
        error_code = SM_WS2811;      // we were unable to claim a state machine
    }

    ws2811_init(pio2811, ws2811sm, ws2811LedsPin);
}


void ws2811_init(PIO pio2811, int sm, uint8_t ws2811LedsPin)
{
    uint offset = pio_add_program(pio2811, &ws2811_program);
    if(offset == -1)
    {
        error_code = PROG_WS2811;
    }

    ws2811_program_init(pio2811, sm, offset, ws2811LedsPin, 800000);
    ws2811_on = true;
}