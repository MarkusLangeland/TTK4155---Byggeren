#pragma once
#include "sam.h"
#include <stdint.h>
#include "motor.h"
#include "can_controller.h"
#include "printf-stdarg.h"

typedef struct {
	float K_p;
	float K_i;
	int16_t error;
	int16_t error_sum; 
	float Timestep;
} pid_values;

void pid_init(pid_values *PID);
int pid_controller(pid_values *PID, CAN_MESSAGE *message);
void reset_sum_errors(pid_values *PID);
