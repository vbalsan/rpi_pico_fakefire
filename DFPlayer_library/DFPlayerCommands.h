#include "pico/stdlib.h"
#include "../globals.h"

# define DFP_START      0x7E  
# define DFP_VER        0xFF  
# define DFP_LEN        0x06  
# define DFP_ACK        0x00   
# define DFP_END        0xEF  


 void DFP_Send(uint8_t CMD, uint8_t Par1, uint8_t Par2);  
 void Serial_init(uart_inst_t *uart_id,uint32_t baudrate,uint8_t tx_pin,uint8_t rx_pin);
