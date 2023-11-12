/*
 * CFile1.c
 *
 * Created: 19.09.2023 17:48:52
 *  Author: nissantk
 */ 
#include "user_input.h"
#include "adc.h"
#include <stdio.h>



userInput get_user_input(uint8_t* adc) {
	int8_t x = (adc_read(CHANNEL1) - 128) / 1.28;
	if (x > Offset) {
		x -= Offset*(100-x)/(100-Offset);
	} else {
		x -= Offset*(-100-x)/(-100-Offset);
	}
	
	int8_t y = (adc_read(CHANNEL2)-128) / 1.28;		
	if (y > Offset) {
		y -= Offset*(100-y)/(100-Offset);
		} else {
		y -= Offset*(-100-y)/(-100-Offset);
	}
	
	uint8_t rightSlider = adc_read(CHANNEL3) /2.55;
	bool right_button_press = adc_read(CHANNEL4)/100;
	uint8_t leftSlider = 0;
	bool left_button_press = 0;

	userInput input = {y, x, rightSlider, leftSlider, left_button_press, right_button_press};			
	return input;
}

Direction get_direction(uint8_t* adc) {
	userInput input = get_user_input(adc);	
		
	if ((input.JoyY > TRESHOLD && (abs(input.JoyX) < abs(input.JoyY))) ) {
		return UP;
		} else if ((input.JoyY < -TRESHOLD) && (abs(input.JoyX) <= abs(input.JoyY))) {
		return DOWN;
		} else if (input.JoyX > TRESHOLD && (abs(input.JoyX) >= abs(input.JoyY))) {
		return RIGHT;
		} else if (input.JoyX < -TRESHOLD && (abs(input.JoyX) > abs(input.JoyY))) {
		return LEFT;
		} else {
			return NEUTRAL;
		} 
	}; 
