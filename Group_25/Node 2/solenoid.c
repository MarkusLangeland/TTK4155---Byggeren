#include "solenoid.h"

#define SOLENOID_IO_PIN PIO_PA22 

void solenoid_init() {
	//Using AD3 which has a pulldown resistor 
	PIOA->PIO_PER |= SOLENOID_IO_PIN;
	PIOA->PIO_OER |= SOLENOID_IO_PIN;
	
	
	PIOA->PIO_SODR |= SOLENOID_IO_PIN; 
}

void solenoid_button(){
	PIOA->PIO_CODR |= SOLENOID_IO_PIN;
	delay_us(100000);
	PIOA->PIO_SODR |= SOLENOID_IO_PIN;
}

