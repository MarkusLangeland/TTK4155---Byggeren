#include "dac.h"
#include <stdbool.h>

void dac_init() {
	
	//DAC ID is 6
	PMC->PMC_PCER1 |= 1 << 6; 
	
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1; //Selecting channel 1
	DACC->DACC_MR |= DACC_MR_WORD_HALF; //16 bit data
	DACC->DACC_MR |= DACC_MR_STARTUP_112; //Sets the startup time to 1024 clock cycles before starting conversion.
	DACC->DACC_CHER = DACC_CHER_CH1; //Enable channel 1 
	
	dac_write(0); 
	
}

void dac_write(int value) {
	DACC-> DACC_CDR = DACC_CDR_DATA(value);
}


