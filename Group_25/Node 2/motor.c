#include "motor.h"

#define MJ2_BITMASK 0b111111110

void motor_init(){
	
	PIOD->PIO_PER |= (MOTOR_EN | MOTOR_DIR | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE); //Configuring Enable register
	PIOD->PIO_OER |= (MOTOR_EN | MOTOR_DIR | MOTOR_SEL | MOTOR_NOT_RST | MOTOR_NOT_OE); //Configuring output enable register	
		 
	PIOC->PIO_PER |= MJ2_BITMASK; 
	PIOC->PIO_ODR |= MJ2_BITMASK;
	
	//PIOD->PIO_CODR |= (MOTOR_NOT_RST);
	//PIOD->PIO_SODR |= (MOTOR_NOT_RST);
	
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER0 |= 1 << (ID_PIOC);
}

void motor_speed(uint16_t value) {
	dac_write(value); 
}

void motor_enable(int state){
	switch (state) {
		case 0:
			PIOD->PIO_CODR = (MOTOR_EN);
			break;
		case 1:
			PIOD->PIO_SODR = (MOTOR_EN);
			break;
	}	
}

void motor_direction_joystick(direction data) {
	switch(data){
		case RIGHT: 
			PIOD->PIO_SODR = (MOTOR_DIR); 
			break;
		case LEFT: 
			PIOD->PIO_CODR = (MOTOR_DIR);  
			break;
	}
}

void motor_direction_slider(direction data) {
	switch(data){
		case RIGHT:
			PIOD->PIO_SODR = (MOTOR_DIR);
			break;
		case LEFT:
			PIOD->PIO_CODR = (MOTOR_DIR);
			break;
	}
}


