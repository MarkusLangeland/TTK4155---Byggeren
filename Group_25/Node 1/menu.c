#include <util/delay.h>
#include <stdbool.h>
#include "user_input.h"
#include "oled.h"
#include "can_controller.h"
#include <time.h>

long long int score = 0;
uint8_t play_mode = 0;


void menu_init() {
	volatile uint8_t* oled = (uint8_t*)0x13ff;
	int selected = 0;
	while (true) {
		int userinput = menu_main(oled, &selected);
		menu_sub(userinput, oled);
	}
}




int menu_main(uint8_t* oled, int* selected) {
	while (true) {
		Direction joyPos = get_direction(oled);
		switch (joyPos)
		{
			case DOWN:
			if (*selected < 2) {
				*selected = *selected + 1;
			} else {
				*selected = 0;
			}
			_delay_ms(600);
			break;
			case UP:
			if (*selected > 0) {
				*selected = *selected - 1;
			} else {
				*selected = 2;
			}
			_delay_ms(600);
			break;
			case RIGHT:
			return *selected;
			break;
			
			case LEFT:
			break;
			default:
			printf("");
			break;
		}
		OLED_pos(0,0);
		OLED_print_string("   Play");
		OLED_pos(1,0);
		OLED_print_string("   Highscore");
		OLED_pos(2,0);
		OLED_print_string("   Settings");
		switch(*selected) {
			case 0:
			OLED_pos(0,0);
			OLED_clear_line(0);
			OLED_print_string("-> Play");
			break;
			case 1:
			OLED_pos(1,0);
			OLED_clear_line(1);
			OLED_print_string("-> Highscore");
			break;
			case 2:
			OLED_pos(2,0);
			OLED_clear_line(2);
			OLED_print_string("-> Settings");
			break;
			default:
			break;
		}
	}
	return -1;
}

void menu_sub(int userInput, uint8_t* oled) {
	switch (userInput) {
		case 0:
		OLED_screen_clear();
		OLED_pos(0,0);
		OLED_print_string("Playing game");
		send_user_input_to_node2();
		OLED_screen_clear();
		return;
		break;
		case 1:
		OLED_screen_clear();
		OLED_pos(0,0);
		OLED_print_string("High score: ");
		break;
		case 2:
		OLED_screen_clear();
		OLED_pos(0,0);
		OLED_print_string("Play modes: ");
		OLED_pos(1,0);
		OLED_print_string(" Move with Joystick");
		OLED_pos(2,0);
		OLED_print_string("  Move with Slider");
		while (true) {
			Direction joyPos = get_direction(oled);
			switch(joyPos) {
				case UP:
					if(play_mode > 0) {
						play_mode--;
					}
					break;
				case DOWN:
					if(play_mode < 1) {
						play_mode++;
					}
					break;
				case LEFT:
					OLED_screen_clear();
					return;
			}
			switch(play_mode) {
				case 0:
					OLED_pos(1,0);
					OLED_clear_line(1);
					OLED_print_string("->  Move with Joystick");
					OLED_pos(2,0);
					OLED_clear_line(2);
					OLED_print_string("    Move with Slider");
					break;
				case 1:
					OLED_clear_line(1);
					OLED_pos(1,0);
					OLED_print_string("    Move with Joystick");
					OLED_pos(2,0);
					OLED_clear_line(2);
					OLED_print_string("->  Move with Slider");
					break;
				default:
					break;
			}
		}
		break;
	}
	while (true) {
		Direction joyPos = get_direction(oled);
		switch (joyPos)
		{
			case LEFT:
			OLED_screen_clear();
			return;
			_delay_ms(600);
			break;
			default:
			printf("");
			break;
		}
	}
}


void send_user_input_to_node2() {
	time_t currentTime;
	struct tm *timeInfo;
	
	volatile uint8_t* node2 = (uint8_t*)0x13ff;
	while(true) {
		userInput input = get_user_input(node2);
		if (input.right_button_press) {
			return;
		}
		OLED_pos(2,0);
		char str[50];
		snprintf(str, sizeof(str), "SCORE: %d", score);
		OLED_print_string(str);
		score++;
		CAN_MESSAGE msg = {111, 8, {input.JoyX, input.JoyY, input.rightSlider, input.right_button_press, play_mode}};
		can_send(&msg);

		
		//Could not get this to work. This need to work for us to be able to have a scoreboard and make the player lose the game
		CAN_MESSAGE messageRecieved;
		if (can_has_message()) {
			printf("Received with ID %u of size %u: \n\r", messageRecieved.id, messageRecieved.data_length);
			for (uint8_t i = 0; i < messageRecieved.data_length; i++) {
				printf("%c, ", messageRecieved.data[i]);
			}
			printf("\n\r");
		}
	}
}