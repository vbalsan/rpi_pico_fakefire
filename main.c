/**
 */


#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "values.h"

#include "pico/stdlib.h"

#include "nec_receive_library/nec_receive.h"
#include "DFPlayer_library/DFPlayerCommands.h"
#include "ws2811_library/ws2811.h"





int main() {

    stdio_init_all();

    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // for leds
    PIO pio2811 = pio0;
    int ws2811sm = 0;
    int ws2811_offset = ws2811_init(pio2811, ws2811sm);
    

    // for ir
    PIO pioIR = pio1;                                 
    uint rx_gpio = IR_GPIO;                              
    int rx_sm = nec_rx_init(pioIR, rx_gpio);         // uses one state machine and 9 instructions


    if (ws2811_offset == -1 || rx_sm == -1) {
        printf("could not configure PIO\n");
        return -1;
    }


    

    uint8_t gidx = 0;
    uint8_t ridx = 0;    
    uint8_t bidx = 0;

    uint8_t main_val   = 0;
    uint8_t main_val10 = 0;
    uint8_t main_val50 = 0;

    uint8_t *g, *r, *b;
    g = &main_val10;
    r = &main_val;    
    b = &main_val50;

    uint32_t pixel;

    // transmit and receive frames
    uint8_t rx_address, rx_data;

    while (1) 
    {
        main_val = red_arr_breathing_2[++ridx]; 
        main_val10 = main_val / 10u;
        main_val50 = main_val / 50u;

        pixel = ugrb_u32( *g,  *r,  *b);

        for (int i = 0; i < NUM_PIXELS -1; ++i) 
        {            
           //put_pixel(pixel);
           put_pixel(0);
        }
        put_pixel(pixel);

        sleep_ms(35);
        
        //r = 255;
        //g = 25;
        //b =0;
        //g = green_arr[++gidx];
        //r = red_arr[++ridx];
        
        // r = red_arr_breathing_2[++ridx];
        // g = (uint8_t)(r/10u);
        // //b = blu_arr[++bidx];
        // b = (uint8_t)(r/50u);

        /*
        printf("\t\n");
        printf("\t\n idx : %d", ridx);
        printf("\t\n value : %d", r);
        printf("\t\n size : %d", sizeof(red_arr_breathing));
        */

        
        // Check if remote has sent message
        while (!pio_sm_is_rx_fifo_empty(pioIR, rx_sm))
        {
            uint32_t rx_frame = pio_sm_get(pioIR, rx_sm);

            if (nec_decode_frame(rx_frame, &rx_address, &rx_data)) 
            {
                printf("\t\nreceived: %02x, %02x", rx_address, rx_data);
                if(rx_address == 0x00)
                {
                    switch (rx_data)
                    {
                    case 0x45:
                        g = &main_val10;
                        r = &main_val;    
                        b = &main_val50;
                        break;

                    case 0x44:
                        r = &main_val10;
                        g = &main_val;    
                        b = &main_val50;
                        break;

                    case 0x07:
                        g = &main_val10;
                        b = &main_val;    
                        r = &main_val50;
                        break;
                    
                    default:
                        g = &main_val10;
                        r = &main_val;    
                        b = &main_val50;
                        break;
                    }
                }
            } 
            else 
            {
                printf("\treceived: %08x", rx_frame);
            }
        }


    }
}
