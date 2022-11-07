#include "pico/stdlib.h"
#include "../globals.h"

# define DFP_START      0x7E  
# define DFP_VER        0xFF  
# define DFP_LEN        0x06  
# define DFP_ACK        0x00   
# define DFP_END        0xEF  

bool                    playback;


void DFP_Send(uint8_t CMD, uint8_t Par1, uint8_t Par2);  
void DFP_SelectSDCard();
void DFP_SetSleepMode();
void DFP_SetNormalMode();
void DFP_Init();
void DFP_PlayTrack(uint8_t folder, uint8_t track);
void DFP_PlayOrPause();
void DFP_Stop();
void DFP_Reset();

void DFP_SetVolume(uint8_t vol);
void DFP_IncreaseVolume();
void DFP_DecreaseVolume();

void DFP_PreviousTrack();
void DFP_NextTrack();

void DFP_SingleRepeatStart();
void DFP_SingleRepeatStop();

void DFP_DACStart();
void DFP_DACStop();

uint8_t highByte(uint16_t value);                            
uint8_t lowByte(uint16_t value);

void Serial_init(uart_inst_t *uart_id,uint32_t baudrate,uint8_t tx_pin,uint8_t rx_pin); 

void DFP_Main_Start();
void DFP_Main_Stop();