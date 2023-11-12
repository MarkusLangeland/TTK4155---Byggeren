#include "sam.h"
#include "stdint.h"
#include "can_config.h"
#include "pwm.h"
#include "adc.h"
#include "motor.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sleep.h"
#include "pid.h"
#include "solenoid.h"

#define LED1 PIO_PA19
#define LED2 PIO_PA20

#define HAS_LOST 1

int main(void) {
	
	configure_uart();
	SystemInit();

	uint32_t can_br = 0;
	can_br |= (ps2 - 1) | ((ps1-1) << 4) | ((proqSeg - 1) << 8) | ((brp_node2 - 1) << 16);
	can_init_def_tx_rx_mb(can_br);
	
	CAN_MESSAGE message;
	
	pwm_init();
	int freq = 84000000; 
	adc_init();  
	motor_init();
	motor_enable(1);
	dac_init();
	solenoid_init();
	int i = 0; 
	
	pid_values PID; 
	pid_init(&PID); 	
	
	int loop_iteration = 0; 
    while (true) 
    {
		if (has_lost_game() == 1) {
			CAN_MESSAGE can_msg;
			can_msg.data[0] = 1;
			can_msg.id = 44;
			can_msg.data_length = 8;
			printf("%c, \n\r CanMSG: ", can_msg.data[0]);
			can_send(&can_msg, 0);
		}
		uint8_t has_message = can_receive(&message, 0);
		if (!has_message) {
			//printf("%d", message.data[4]);
			if (message.data[4] == 0) {
					run(&message);
				} else {
				for (int i = 0; i < 3; i++) {
					run2(&message, &PID);
				}
				reset_sum_errors(&PID);
			}		
		}
    }
}

int has_lost_game() {
	uint16_t value = adc_read(); 
	printf("%d \n\r, ", value);	
	if ((value < 1400) && (value != 0)){
		//printf("You lost! \n\r");
		return 1;
	}
	return 0;
}


typedef struct {
	uint16_t ID;
	uint8_t length;
	char data[8];
} message_type;


void run(CAN_MESSAGE * message) {
		float test = (float)((message->data[2]) / 10000.0);
		test = roundf(test*400)/40;
		//test = test < 1.4 && test > 1.6 ? test
		pwm_set_duty_cycle(test);
		
		
		int TRESHOLD_HORISONTAL = 15;
		int TRESHOLD_VERTICAL = 50;
		int horisontal = message->data[0];
		int vertical = message->data[1];
		
		if (horisontal < -TRESHOLD_HORISONTAL) {
			
			dac_write(1700);
			if (horisontal < -95) {
				dac_write(2500);
			}
			motor_direction_joystick(LEFT);
			} else if(horisontal > TRESHOLD_HORISONTAL) {
			
			dac_write(1700);
			if (horisontal > 95) {
				dac_write(2500);
			}
			motor_direction_joystick(RIGHT);
			} else if(vertical > TRESHOLD_VERTICAL) {
				dac_write(0);
				solenoid_button();
			} else {
			dac_write(0);
		}

	
}


void run2(CAN_MESSAGE * message, pid_values *PID) {
		
		float real_value =((float)(message->data[0]+100)/1400.0);
		float stable_value = real_value > 0.06 && real_value < 0.09 ? 0.075 : real_value;
		pwm_set_duty_cycle(stable_value);
		
		int TRESHOLD_VERTICAL = 50;
		int vertical = message->data[1];
		if(vertical > TRESHOLD_VERTICAL) {
			dac_write(0);
			solenoid_button();
			}
		int u = pid_controller(PID, message);
		if (u < 0 )
		{
			motor_direction_slider(LEFT);
			motor_speed((uint16_t) abs(u)); 
		}
		else if (u > 0) 
		{
			motor_direction_slider(RIGHT);
			motor_speed((uint16_t) abs(u));		
		}
}