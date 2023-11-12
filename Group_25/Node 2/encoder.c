#include "encoder.h"

int16_t encoder_read(){
	
	PIOD->PIO_SODR |= (MOTOR_NOT_RST);
	PIOD->PIO_CODR |= (MOTOR_NOT_OE);
	PIOD->PIO_CODR |= (MOTOR_SEL);
	
	delay_us(50);
	
	uint16_t high_byte = (PIOC->PIO_PDSR & MJ2_BITMASK) >> 1;
	PIOD->PIO_SODR |= (MOTOR_SEL);
	
	delay_us(50);
	uint16_t low_byte = (PIOC->PIO_PDSR & MJ2_BITMASK) >> 1;
	
	PIOD->PIO_SODR |= (MOTOR_NOT_OE);
	
	uint16_t encoder_value = (high_byte << 8) | low_byte;
	int16_t signed_value = *(int16_t *)&encoder_value;

	return (int)signed_value/14.0;
}


