#include "stdint.h"
#include "spi_com_driver.h"
#include <stdio.h>
#include <avr/io.h>


void SPI_init(void)
{
		
	DDRB |= (1<<PB5) | (1<<PB7) | (1<<PB4);
	
	//Set MISO low
	DDRB &= ~(1<<PB6);  
	
	//Set SPI, Master, set clock rate fck/16 from datasheet page 160.
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0); 
}

void cs_on(void){ 
	PORTB &= ~(1 << PB4); 
}

void cs_low(void){
	PORTB |= (1 << PB4);
}


uint8_t SPI_write(uint8_t cData){
	SPDR = cData;
	while(!(SPSR & (1<<SPIF))){};  
	return SPDR;
}

uint8_t SPI_read(void) {
	SPI_write(0); 
	return SPDR;  
}

