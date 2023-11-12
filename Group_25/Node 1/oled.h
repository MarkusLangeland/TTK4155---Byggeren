#pragma once 

static void write_c(uint8_t data);  
void OLED_init(); 
void OLED_fill_screen();
void OLED_screen_clear(); 
void OLED_pos();
void OLED_goto_col();
void OLED_goto_line();
void OLED_print_char(char c);
void OLED_print_string(char* letters);
void OLED_clear_line(uint8_t line);
	

