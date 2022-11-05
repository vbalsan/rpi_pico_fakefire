#ifndef GLOBALS_H
#define GLOBALS_H

#include "pico/stdlib.h"

//leds
//#define IS_RGBW         false
#define NUM_PIXELS      50
#define WS2811_PIN      15
#define WS2811_PIO      pio0

//IR
#define IR_GPIO         18
#define IR_PIO          pio1

//uart
#define UART_ID         uart0
#define BAUD_RATE       115200

#define UART_TX_PIN     16
#define UART_RX_PIN     17

uint8_t                 error_code;
bool                    uart_on;
bool                    ws2811_on;

enum LED_PATTERNS
{
    NO_ERROR = 0,
    SM_WS2811,
    PROG_WS2811,
    SM_IR,
    PROG_IR,
    UART
};

#endif