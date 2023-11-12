#pragma once 
#include "sam.h"
#include "dac.h"
#include <stdbool.h>
#include "sleep.h"

#define MOTOR_EN PIO_PD9
#define MOTOR_DIR PIO_PD10
#define MOTOR_SEL PIO_PD2
#define MOTOR_NOT_OE PIO_PD0
#define MOTOR_NOT_RST PIO_PD1

#define MJ2_BITMASK 0b111111110


typedef enum {
	RIGHT,
	LEFT
} direction;




void motor_init();
void motor_direction_slider(direction data);
void motor_direction_joystick(direction data);
void motor_speed(uint16_t value);
void motor_enable(int state);
void motor_encoder_reset();
