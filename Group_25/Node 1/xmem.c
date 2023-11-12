#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include "xmem.h"
#include "stdint.h"

uint16_t BASE_ADDRESS = 0x0;

//This is taken directly from the labmanual
void xmem_init(void){
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << (XMM2));
	SFIOR |= (XMM1 || XMM0 && 0);
}

void xmem_write(uint8_t data, uint16_t addr){
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	ext_mem[addr] = data;
}

uint8_t xmem_read(uint16_t addr){
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	uint8_t ret_val=ext_mem[addr];
	return ret_val;
}

