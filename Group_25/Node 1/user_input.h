/*
 * IncFile1.h
 *
 * Created: 19.09.2023 18:18:26
 *  Author: nissantk
 */ 
#pragma once
#include <stdio.h>
#include <stdbool.h>

#define Offset 25
#define TRESHOLD 80

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL,
	} Direction;

typedef enum {
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	} CHANNELS;


typedef struct {
	int8_t JoyX;
	int8_t JoyY;
	uint8_t rightSlider;
	uint8_t leftSlider;
	bool left_button_press;
	bool right_button_press;
	} userInput;

userInput get_user_input(uint8_t* adc);
Direction get_direction(uint8_t* adc);


