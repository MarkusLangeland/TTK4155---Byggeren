#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"
#include "xmem.h"
#include "sram.h"
#include "adc.h"
#include "stdint.h"
#include "user_input.h"
#include "oled.h"
#include "font.h"
#include "spi_com_driver.h"
#include "mcp2515.h"
#include "can_controller.h"
#include "menu.h"

#define IO_OUTPUT 1
#define BAUD 9600
#define UBRR 4915200UL / 16 / BAUD - 1 

int main(void)
{
	uart_init(UBRR);
	xmem_init(); 
	OLED_init(); 
	printf("\n\r");
	can_init();
	
	
	menu_init();
	
	
		CAN_MESSAGE message1; 
		CAN_MESSAGE msg_res;
		message1.id = 1; 
		message1.data[0] = 2;
		message1.data_length = 1; 
		
		while(true){
			can_send(&message1); 
			_delay_ms(100);
		
			can_recieve(&msg_res);
			printf("Received with ID %u of size %u: \n\r", msg_res.id, msg_res.data_length);
			for (uint8_t i = 0; i < msg_res.data_length; i++) {
				printf("%c, ", msg_res.data[i]);
			}
			printf("\n\r");
		}
		
		
}

void printUART(uint8_t address) { 

	uint8_t value = mcp2515_read(address);
	
	// Print the value in binary representation
	for (int i = 7; i >= 0; i--) {
		printf("%u", (value >> i) & 1);
	}

	printf("\n\r");  // Move to the next line after printing the binary value
}

