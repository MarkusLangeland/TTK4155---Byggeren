#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include "font.h"
#include "oled.h"

static void OLED_write_command(uint8_t command){
	volatile char* command_address = (char*)0x1000;
	command_address[0] = command; 
}

static void OLED_write_data(uint8_t data){
	volatile uint8_t* data_address = (uint8_t*) 0x1200;
	data_address[0] = data; 
}

void OLED_goto_line(int line) {
	if (line >= 0 && line <=7) {
		OLED_write_command(0xb0+line);	
	} else {
		printf("ERROR: Invalid line!");
	}
}

void OLED_clear_line(uint8_t line) {
	OLED_goto_line(line);
	OLED_goto_col(0);
	for (int j = 0; j <= 127; j++){
		OLED_write_data(0);
	}
}



void OLED_goto_col(int col) {
	if (col >= 0 && col <= 127){
		OLED_write_command(0x21);
		OLED_write_command(col);
		OLED_write_command(0xFF);
	}
}



void OLED_pos(int line, int col) {
		OLED_goto_line(line);
		OLED_goto_col(col);
}


//Directly extracted from the datasheet for the OLED from page 15 
void OLED_init()
{
	OLED_write_command(0xae); // display off
	OLED_write_command(0xa1); //segment remap
	OLED_write_command(0xda); //common pads hardware: alternative
	OLED_write_command(0x12);
	OLED_write_command(0xc8); //common output scan direction:com63~com0
	OLED_write_command(0xa8); //multiplex ration mode:63
	OLED_write_command(0x3f);
	OLED_write_command(0xd5); //display divide ratio/osc. freq. mode
	OLED_write_command(0x80);
	OLED_write_command(0x81); //contrast control
	OLED_write_command(0x50);
	OLED_write_command(0xd9); //set pre-charge period
	OLED_write_command(0x21);
	OLED_write_command(0x20); //Set Memory Addressing Mode
	OLED_write_command(0x02);
	OLED_write_command(0xdb); //VCOM deselect level mode
	OLED_write_command(0x30);
	OLED_write_command(0xad); //master configuration
	OLED_write_command(0x00);
	OLED_write_command(0xa4); //out follows RAM content
	OLED_write_command(0xa6); //set normal display
	OLED_write_command(0xaf); // display on
	OLED_write_command(0x20); //Set Memory Addressing Mode
	OLED_write_command(0x02);
	OLED_screen_clear(); 
}

void OLED_print_char(char letter){
	if (letter >= ' ' && letter <= '~'){
		for (int i = 0; i < 5; i++){
			uint8_t c = pgm_read_byte(&(font5[letter - 32][i]));
			OLED_write_data(c);
		}
	} 
}

void OLED_print_string(char* letters) {
	int i = 0;
	while (letters[i] != '\0') {
		if (letters[i] >= ' ' && letters[i] <= '~'){
			OLED_print_char(letters[i]);
		}
		++i;
	}
}

void OLED_screen_clear(){
	for (int i = 0; i <= 7; i++){
		OLED_write_command(0xb0+i);
		for (int j = 0; j <= 127; j++){
			OLED_write_data(0);
		}
	}		
}

