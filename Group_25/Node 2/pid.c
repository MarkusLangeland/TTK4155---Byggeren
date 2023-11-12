#include "pid.h"
#include "motor.h"
#include "encoder.h"
#include "can_controller.h"

const float K_i_value = 0.5;
const float K_p_value = 40;
const float pid_time_step = 200; //change value later 

void pid_init(pid_values *PID){
	PID->K_i = K_i_value; 
	PID->K_p = K_p_value; 
	PID->error = 0;
	PID->error_sum = 0;  
	PID->Timestep = pid_time_step; 
}

int pid_controller(pid_values *PID, CAN_MESSAGE *message){
	int16_t yref = (int16_t)message->data[2];

	//obtain decoder value
	int16_t decoder_value = encoder_read();
	
	//calculate errors
	PID->error = yref + decoder_value;
	PID->error_sum += PID->error; 
	
	int u = K_p_value*PID->error + K_i_value*PID->error_sum*0;
	int u_inside_range = u > 2000 ? 2000 : u;
	printf("ERROR: %d ENCODER: %d\n\r", PID->error, decoder_value);
	return  u_inside_range; 
}

void reset_sum_errors(pid_values *PID){
	PID->error = 0; 
	PID->error_sum = 0; 
}
