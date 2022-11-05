#include "DFPlayerCommands.h"
#include "hardware/uart.h"


void Serial_init(uart_inst_t *uart_id, 
                uint32_t baudrate,
                uint8_t tx_pin,
                uint8_t rx_pin)
{
    uart_init(uart_id, baudrate);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);

    uart_on = true;
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

  // Send the command line to DFPlayer  
  for (uint8_t idx = 0; idx < 10; idx++)
  {
       uart_putc_raw(UART_ID, Full_Command[idx]);
  }
 }

void DFP_Read_Fire()
{

}