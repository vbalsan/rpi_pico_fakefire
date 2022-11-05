/**
 */

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "../globals.h"

// public API

void IR_init(PIO pioIR, uint8_t rx_gpio);
int nec_rx_init(PIO pio, uint pin);
bool nec_decode_frame(uint32_t sm, uint8_t *p_address, uint8_t *p_data);
bool is_there_message();
uint32_t get_message();

int rx_sm;