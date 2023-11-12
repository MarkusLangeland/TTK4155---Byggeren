#include "sleep.h" 


//delay function
void delay_us(int us) {
	for(int i = 0; i < 5*us; i++) {
		__asm__("nop");
	}
}