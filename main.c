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





int main() 
{
    uart_on   = false;                  // flag for uart errors
    ws2811_on = false;                  // flag for leds errors

    uint32_t rx_frame;                  // For IR frame, 32 bits message    
    uint8_t  rx_address, rx_data;       // received IR data

    uint8_t main_idx = 0;               // Index for main array of values

    uint8_t main_val   = 0;             // main_val is equal to the current value in array
    uint8_t main_val10 = 0;             // same as main_val but divided by 10
    uint8_t main_val50 = 0;             // same as main_val but divided by 50

    uint8_t *pGreenVal;                 // Pointer to the value of green (can be full, /10 or /50)
    uint8_t *pRedVal;                   // Pointer to the value of red (can be full, /10 or /50)
    uint8_t *pBlueVal;                  // Pointer to the value of blue (can be full, /10 or /50)

    pGreenVal   = &main_val10;          //
    pRedVal     = &main_val;            // Default assignation to red colour
    pBlueVal    = &main_val50;          //

    uint32_t pixel;                     // 32 bits value passed to the PIO state machine

    stdio_init_all();

    Serial_init(UART_ID,                //
                BAUD_RATE,              // for serial
                UART_TX_PIN,            //
                UART_RX_PIN);           // 

    Leds_init(WS2811_PIO, WS2811_PIN);  // for leds       

    IR_init(IR_PIO, IR_GPIO);           // for ir    
    

    while (!error_code) 
    {
        //main_val   = red_arr[++main_idx]; 
        //main_val10 = main_val / 10u;
        //main_val50 = main_val / 50u;

        //pixel = ugrb_u32( *pGreenVal,  *pRedVal,  *pBlueVal);
        

        for (uint8_t i = 0; i < NUM_PIXELS; i++) 
        {  
            uint8_t idx = main_idx + i;
            main_val   = red_arr2[idx]; 
            main_val10 = main_val / 16u;
            main_val50 = main_val / 64u;

            pixel = ugrb_u32( *pGreenVal,  *pRedVal,  *pBlueVal);          
            put_pixel(pixel);
            //put_pixel(0);
        }
        //put_pixel(pixel);
        main_idx++;
        // make a break to lock the pixels       
        sleep_ms(50);

        
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
        while (!is_there_message())
        {
            rx_frame = get_message();
            if (nec_decode_frame(rx_frame, &rx_address, &rx_data)) 
            {
                //printf("\t\nreceived: %02x, %02x", rx_address, rx_data);
                if(rx_address == 0x00)
                {
                    switch (rx_data)
                    {
                    case 0x45:
                        pGreenVal = &main_val10;
                        pRedVal = &main_val;    
                        pBlueVal = &main_val50;
                        break;

                    case 0x44:
                        pRedVal = &main_val10;
                        pGreenVal = &main_val;    
                        pBlueVal = &main_val50;
                        break;

                    case 0x07:
                        pGreenVal = &main_val10;
                        pBlueVal = &main_val;    
                        pRedVal = &main_val50;
                        break;
                    
                    default:
                        pGreenVal = &main_val10;
                        pRedVal = &main_val;    
                        pBlueVal = &main_val50;
                        break;
                    }
                }
            } 
            else 
            {
                printf("\t received: %08x", rx_frame);
            }
        }


    }

    // out of while, error happened
    if(uart_on)
    {

    }

    if(ws2811_on)
    {

    }

    switch (error_code)
    {
    case SM_WS2811:
        
        break;

    case PROG_WS2811:
        break;

    case SM_IR:
        break;
    
    case PROG_IR:
        break;

    case UART:
        break;

    default:
        break;
    }



}
