#include "adc.h"


void adc_init() {
	
	ADC->ADC_MR = ADC_MR_FREERUN;// continuos measure in this mode 
	ADC-> ADC_CHER = ADC_CHER_CH0;  //enabling the channel we are gonna use 
	
	//ADC id is 37
	PMC->PMC_PCER1 |= 1 << 5; 
	
	ADC->ADC_CR = ADC_CR_START; 
}

uint16_t adc_read(){
	uint16_t value = ADC->ADC_CDR[0];
	return value; 
}


