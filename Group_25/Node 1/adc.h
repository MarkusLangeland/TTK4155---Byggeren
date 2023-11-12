#pragma once
#include <util/delay.h>
#include <avr/io.h>

#define BASE_ADDRESS_ADC 0x1400
#define NUMBER_OF_CHANNELS 4
#define F_CPU 4915200UL

uint8_t adc_read(uint8_t channel);
void adc_init(void) ;

typedef enum{
	ADC_A0,
	ADC_A1,
	ADC_UNUSED,
	ADC_POWER_DOWN,
	ADC_INHIBIT_CONVERSION,
	ADC_BIPOLAR,
	ADC_DIFFERENTIAL,
	ADC_CONVERT_SINGLE
} adc_config_t;
