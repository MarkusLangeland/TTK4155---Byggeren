#include "uart.h"

//1. define ports
//2. send and transmitt signal


//USART_init er hentet rett fra boken. Side 172 i kilde: https://learn-eu-central-1-prod-fleet01-xythos.content.blackboardcdn.com/5def77a38a2f7/309080?X-Blackboard-S3-Bucket=learn-eu-central-1-prod-fleet01-xythos&X-Blackboard-Expiration=1693839600000&X-Blackboard-Signature=9KvQ0h28BrglOqy60TPsanzsGhP5mqPjbQW6dRUtpBI%3D&X-Blackboard-Client-Id=303508&X-Blackboard-S3-Region=eu-central-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27Microcontroller%2520ATmega162.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEGoaDGV1LWNlbnRyYWwtMSJGMEQCICgt092rEboss%2FCyK9U5jvu7EBgDswqx1VW0Qosqe0YGAiAVIL0JC%2FUVYVnotQdVDpnWNVeMcf61%2BoxbUkrEYZuZbCq9BQhEEAMaDDYzNTU2NzkyNDE4MyIMWpDsn3Q20GoCPtLjKpoF7rGx0pOnX0k2istTNnhuBtD5ZEJxz9WnJiUHhO8bfL20kaZI8Ey7VV5v5IB3dvy2MflXG8i7wdERtr4YkmtMMICGjp%2BOwb1aCD6VYB%2BxJz9MGwelPziRDn59F2WkC%2BmlGi3BaaHecWF9bx9wMbCTjFdMbDvINgKn6dvoD2Tmtah3nOwsqzsS%2FPWYAyJ6%2BqOB1WBAtsE4OIMMy6qWtbIYGUqQu61EzLD%2BH8GOs9AKiQyIFVc8i1LiLymVFyymiVwUd4Bq%2FQ%2FNfkBQgKMNmLLXq6pm0yzZOLp2ldfnvuUGDrPrUXny2BoPDCnaClhtW%2FK9QOZn7j5JLq8M3oTqkewQ8PwAl2gQ2UX3iL2YPm0B6Mu9r8%2BZgj3KHBqE%2FlMI%2FHp1ys%2FfzlcBc2IxlwTRrtGZJu5aHMoY8r%2F3TTPFC8CsHBS5sJqdLIkFm8aq4iKB8wYBSE4TKc4i89OGbdWZQd8rsbHR3dEfTXbL43MmNm3ShnLBXpI0pW%2F17UK2yvYKckJ7q54tVhM7rnLyPekan%2B7lcHgjBQE2pkoCNb1IvQKc60sN3yeYpHkpzUslLRD%2BAIRuYLRvmqHYATe7Cn3Kz3FLvMi7fp4uyAhR6M8pmmqqLi172qsSJkXRT7EZVeKI2GsAvNTJvALhJMk1e3oFSDXO4n8mD2weRvQgZCvs5HyKBA8Lw4ZgF074NlKJcbqf7GeS9IxF7%2FdWwMXkHg%2BRJ1KPZJQW%2FqIJTiVTRNRptw30OnJvMkn1qLvajJ9bcG90yvaDS2%2BiSU123z26X2j2OPBmPRF6b9tgmmfLZpQapiZ%2BcsFpXRee5o8uDYITi%2B5z2ZlNJmfR8Zbo%2FkUqY7r%2B6828B3R59mZsWcZVKhq4DSATb7ep7qXNvezygOXiMJng1qcGOrIB0%2FXlT6sEDIaqQMEBgsK0%2BzXEiB6zEwsuHoLW0fcvDh19bf5%2BVvz%2FK6NtaxDEQWYPAnTlBFMupmxUH3R6pi%2B3qZK9tr11cztKZ9bR1v%2FuqSaPc1l20ii%2FWu5b91RE22E6N2o5NtTArPVluRIMWYLJYdznoySoIOONPu8yNX0MSsZg03hfE56iUvSWjff82LGbiD1GFrel5dajS12z6H%2FGC%2Bvh%2B%2By5qVRCOZyo1WVfMdK4dg%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20230904T090000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PL324CQ6CS%2F20230904%2Feu-central-1%2Fs3%2Faws4_request&X-Amz-Signature=f885a7fa13b05c6520ae8984806f48a0da2dd845ca092ba2771d255a6c3b4d22

void uart_init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	fdevopen(&uart_transmit, &uart_receiver);
}

void uart_transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char uart_receiver( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A) & (1<<RXC0));
	/* Get and return received data from buffer */
	return UDR0;
}

