#include "DFPlayerCommands.h"
#include "hardware/uart.h"

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

  // Send the command line to DFPlayer  
  for (uint8_t idx = 0; idx < 10; idx++)
  {
       uart_putc_raw(UART_ID, Full_Command[idx]);
  }
 }