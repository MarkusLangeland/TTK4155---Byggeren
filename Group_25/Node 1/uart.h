#pragma once
#include <avr/io.h>

void uart_init( unsigned int ubrr );
void uart_transmit( unsigned char data );
unsigned char uart_receiver( void );

