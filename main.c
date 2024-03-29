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

uint8_t main_val   = 0;             // main_val is equal to the current value in array
uint8_t main_val10 = 0;             // same as main_val but divided by 10
uint8_t main_val50 = 0;             // same as main_val but divided by 50

uint8_t *pGreenVal;                 // Pointer to the value of green (can be full, /10 or /50)
uint8_t *pRedVal;                   // Pointer to the value of red (can be full, /10 or /50)
uint8_t *pBlueVal;                  // Pointer to the value of blue (can be full, /10 or /50)

void SetGreen()
{
    pRedVal = &main_val10;
    pGreenVal = &main_val;    
    pBlueVal = &main_val50;
}

void SetRed()
{
    pGreenVal = &main_val10;
    pRedVal = &main_val;    
    pBlueVal = &main_val50;
}

void SetBlue()
{
    pGreenVal = &main_val10;
    pBlueVal = &main_val;    
    pRedVal = &main_val50;
}

void set_power_leds(bool mosfet_val)  
{
    if (mosfet_val)
    {
        gpio_put(FET_PIN, 1);
    }
    else
    {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) 
        {          
            put_pixel(0);
        }
        gpio_put(FET_PIN, 0);
    }
}


void process_rx_data(uint8_t rx_data)
{
    switch (rx_data)
    {
    case 0x45:                      // on off                        
        SysActive = !SysActive;

        if(SysActive)
        {
            gpio_put(SYSLED, 1);
            set_power_leds(true);   // turn on MOSFET
            sleep_ms(20);
            SetRed();
            DFP_Main_Start();            
        }
        else 
        {
            gpio_put(SYSLED, 0);
            set_power_leds(false);  // stop MOSFET
            DFP_Main_Stop();
        }        
        break;

    case 0x44:                      // Test
        SetGreen(); 
        DFP_PlayTrack(1,2);
        break;

    case 0x40:                      // +
        DFP_IncreaseVolume();
        break;

    case 0x19:                      // -
        DFP_DecreaseVolume();
        break;

    case 0x47:                      // menu
        break;

    case 0x07:                      // <<
        DFP_PreviousTrack();
        break;

    case 0x09:                      // >>
        DFP_NextTrack();
        break;

    case 0x43:                      // return
        break;
    case 0x0D:                      // C
        break;

    case 0x15:                      // play
        DFP_PlayOrPause();
        break;

    case 0x16:                      // 0
        SetRed();
        break;
    case 0x0C:                      // 1
        SetBlue();
        break;
    case 0x18:                      // 2
        SetGreen();
        break;
    case 0x5E:                      // 3
        SetRed();
        break;
    case 0x08:                      // 4
        SetRed();
        break;
    case 0x1C:                      // 5
        SetRed();
        break;
    case 0x5A:                      // 6
        SetRed();
        break;
    case 0x42:                      // 7
        SetRed();
        break;
    case 0x52:                      // 8
        SetRed();
        break;
    case 0x4A:                      // 9
        SetGreen(); 
        DFP_PlayTrack(1,3);
        break;
    
    default:
        break;
    }
}

void ir_receive_and_exec()
{
    uint32_t rx_frame;                          // For IR frame, 32 bits message    
    uint8_t  rx_address, rx_data;               // received IR data

    while (!is_fifo_empty())
    {
        rx_frame = get_message();
        if (nec_decode_frame(rx_frame, &rx_address, &rx_data)) 
        {
            if(rx_address == 0x00)
            {
                process_rx_data(rx_data);                        
            }
        } 
        else 
        {
            printf("\t received: %08x", rx_frame);
        }
    }
}

void adjust_light(uint8_t *main_val, uint8_t *main_val10, uint8_t *main_val50, uint8_t luminosity)
{
    uint16_t tempvar = 0;

    tempvar = (uint16_t)(*main_val * (luminosity + 1));
    *main_val = tempvar >> 8;

    tempvar = (uint16_t)(*main_val10 * (luminosity + 1));
    *main_val10 = tempvar >> 8;

    tempvar = (uint16_t)(*main_val50 * (luminosity + 1));
    *main_val50 = tempvar >> 8;
}


/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
int main() 
{
    sleep_ms(3000);                            // Some time for peripherals to get ready
    gpio_init(FET_PIN);
    gpio_set_dir(FET_PIN, GPIO_OUT);
    
    SysActive  = true;                         // System is "off", trigger or not the MOSFET
    error_code = NO_ERROR;      
    set_power_leds(true);                      // MOSFET

    uart_on   = false;                          // flag for uart errors
    ws2811_on = false;                          // flag for leds errors    

    uint8_t main_idx = 0;                       // Index for main array of values    
    uint8_t luminosity = 0;

    pGreenVal   = &main_val10;                  //
    pRedVal     = &main_val;                    // Default assignation to red colour
    pBlueVal    = &main_val50;                  //

    uint32_t pixel;                             // 32 bits value passed to the PIO state machine

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    
    
    gpio_init(SYSLED);
    gpio_set_dir(SYSLED, GPIO_OUT);
    gpio_put(SYSLED, 1);

    gpio_init(ERROR_LED);
    gpio_set_dir(ERROR_LED, GPIO_OUT);

    stdio_init_all();       

    Serial_init(UART_ID,                        //
                BAUD_RATE,                      // for serial
                UART_TX_PIN,                    //
                UART_RX_PIN);                   // 

    Leds_init(WS2811_PIO, WS2811_PIN);          // for leds       

    IR_init(IR_PIO, IR_GPIO);                   // for ir    


    DFP_Init();                                 // Initialization of DFPlayer
    sleep_ms(3000);
    DFP_SetVolume(0x00);                        // Volume at 0x00/0x30

/*****/
    sleep_ms(1000);
    SetRed();
    
    DFP_Main_Start();
    DFP_SetBass();
    DFP_SetVolume(0x30);

/*****/
    while (!error_code)                         // Main loop, if no error
    {
        /********* LOOP FOR OFF *********/
        while(!SysActive)                       // If system is off we check IR
        {            
            ir_receive_and_exec();            
            sleep_ms(100);
        }

        /********* LOOP FOR ON *********/
        while(SysActive)                        // If system is on
        {

            for (uint8_t i = 0; i < 3; i++) // Yellow
            {  
                uint8_t idx = main_idx + i;
                main_val   = yellow_array_dec[idx]; 
                main_val10 = main_val / 2u;
                main_val50 = main_val / 5u;

                if (luminosity != 0xFF)
                {
                    adjust_light(&main_val, &main_val10, &main_val50, luminosity);
                }

                pixel = ugrb_u32( *pGreenVal,  
                                  *pRedVal,  
                                  *pBlueVal);          
                put_pixel(pixel);
            }
            for (uint8_t i = 0; i < (NUM_PIXELS - 3); i++) // Red
            {  
                uint8_t idx = main_idx + i;
                main_val   = red_arr[idx]; 
                main_val10 = main_val / 16u;
                main_val50 = main_val / 64u;

                if (luminosity != 0xFF)
                {
                    adjust_light(&main_val, &main_val10, &main_val50, luminosity);
                }

                pixel = ugrb_u32( *pGreenVal,  
                                  *pRedVal,  
                                  *pBlueVal);          
                put_pixel(pixel);
            }
            
            main_idx++;
                   
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            sleep_ms(50);                       // make a break to lock the pixels        
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            
            ir_receive_and_exec();              // Check if remote has sent message

            if (luminosity != 0xFF)
            {
                luminosity++;
            }
        }
        luminosity = 0;
    }

    /**********************************/
    /** out of while, error happened **/
    /**********************************/
    if(uart_on)
    {

    }

    if(ws2811_on)
    {

    }

    while(1)
    {    
        switch (error_code)
        {
            case SM_WS2811:
                gpio_put(ERROR_LED, 1);
                sleep_ms(50);                       
                gpio_put(ERROR_LED, 0);
                
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



}
