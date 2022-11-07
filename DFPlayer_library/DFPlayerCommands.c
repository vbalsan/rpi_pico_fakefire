#include "DFPlayerCommands.h"
#include "hardware/uart.h"


void Serial_init(uart_inst_t *uart_id, 
                uint32_t baudrate,
                uint8_t tx_pin,
                uint8_t rx_pin)
{
    uart_init(uart_id, baudrate);

    uart_set_format(uart_id, 8 , 1 , UART_PARITY_NONE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);

    uart_on = true;
}

void DFP_Init()
{
    DFP_Send(0x3F, 0x00, 0x00);       // Initialization
    sleep_ms(30);
    DFP_SelectSDCard();    
    DFP_DACStart(); 
}



void DFP_PlayTrack(uint8_t folder, uint8_t track)
{
    DFP_Send(0x0F,folder,track);
    sleep_ms(30);
    DFP_SingleRepeatStart();
}

void DFP_PlayOrPause()
{
    if(playback)
    {
        DFP_Send(0x0E,0x00, 0x00);
        sleep_ms(30);
        playback = false;
    }
    else
    {
        DFP_Send(0x0D,0x00, 0x00);
        sleep_ms(30);
        playback = true;
    }
}


void DFP_Stop()
{
    DFP_Send(0x16,0x00,0x00);
    sleep_ms(30);
}

void DFP_SingleRepeatStart()
{
    DFP_Send(0x19,0x00,0x00);
    sleep_ms(30);
}

void DFP_SingleRepeatStop()
{
    DFP_Send(0x19,0x00,0x01);
    sleep_ms(30);
}

void DFP_DACStart()
{
    DFP_Send(0x1A,0x00,0x00);
    sleep_ms(30);
}

void DFP_DACStop()
{
    DFP_Send(0x1A,0x00,0x01);
    sleep_ms(30);
}

void DFP_SelectSDCard()
{
    DFP_Send(0x09,0x00,0x02);       
    sleep_ms(30);    
}

void DFP_SetSleepMode()
{
    DFP_Send(0x0A,0x00,0x00);       
    sleep_ms(30);    
}

void DFP_SetNormalMode()
{
    DFP_Send(0x0B,0x00,0x00);       
    sleep_ms(30);    
}

void DFP_Reset()
{
    DFP_Send(0x0C,0x00,0x00);       
    sleep_ms(30);    
}

// Well, there is a command increase/decrease soooo...
/*
void DFP_DecreaseVolume()
{
    if(main_volume >= 0x01)
    {
        DFP_Send(0x06,0x00,--main_volume);       
        sleep_ms(30);
    }
}

void DFP_IncreaseVolume()
{
    if(main_volume <= 0x2F)
    {
        DFP_Send(0x06,0x00,++main_volume);       
        sleep_ms(30);
    }    
}
*/
void DFP_DecreaseVolume()
{
    DFP_Send(0x05,0x00,0x00);       
    sleep_ms(30);    
}

void DFP_IncreaseVolume()
{
    DFP_Send(0x04,0x00,0x00);       
    sleep_ms(30);    
}

void DFP_PreviousTrack()
{
    DFP_Send(0x02,0x00,0x00);       
    sleep_ms(30);    
}

void DFP_NextTrack()
{
    DFP_Send(0x01,0x00,0x00);       
    sleep_ms(30);    
}

void DFP_SetVolume(uint8_t vol)
{
    if(vol <= 0x30)
    {
        DFP_Send(0x06,0x00,vol);       
        sleep_ms(30);
    }
    else
    {
        vol = 0x30;
        DFP_Send(0x06,0x00,0x30);   // Volume max
        sleep_ms(30);
    }
    main_volume = vol;
}



uint8_t highByte(uint16_t value)
{
    return (value >> 8);
}
                            
uint8_t lowByte(uint16_t value)
{
    return (value & 0xFF);
}

void DFP_Send(uint8_t Command, uint8_t Par1, uint8_t Par2)
{   
  
  // Calculate the checksum (2 bytes)  
  uint16_t checksum = -(DFP_VER + DFP_LEN + Command + DFP_ACK + Par1 + Par2);

  // Build the command line  
  uint8_t Full_Command[10] = { DFP_START, 
                            DFP_VER, 
                            DFP_LEN, 
                            Command, 
                            DFP_ACK,
                            Par1, 
                            Par2, 
                            highByte(checksum), 
                            lowByte(checksum), 
                            DFP_END};
    
  for (uint8_t idx = 0; idx < 10; idx++)            // Send the command line to DFPlayer
  {
       uart_putc_raw(UART_ID, Full_Command[idx]);
  }
 }

void DFP_Main_Start()
{
    DFP_SelectSDCard();    
    DFP_SetVolume(0x10);
    DFP_PlayTrack(1,1);
    playback = true;
}

void DFP_Main_Stop()
{    
    DFP_SetVolume(0x00);                            
    DFP_Stop();
    playback = false;
    DFP_SetSleepMode();
}