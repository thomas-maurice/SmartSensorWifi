/**
 * \file serial.c
 * \author Thomas Maurice
 * 
 * \brief Serial port management file
 * \version 0.1
 * 
 */

#include <serial.h>

void serial_init(void)
{
	// ATMEGA8
	/*UBRRH = (BAUDRATE>>8);
	UBRRL = BAUDRATE;
	UCSRA = 0;
	UCSRB= (1<<URSEL)|(1<<RXEN)|(1<<TXEN);
	UCSRB|= (1 << RXCIE);*/
	// ATMEGA328
	UBRR0H = (BAUDRATE>>8);
	UBRR0L = BAUDRATE;	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);//0x06;
}

/**
 * \brief Sends a byte through the serial link
 */
void serial_send(unsigned char c) {
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=c;
}

void serial_send_string(char* s, int size) {
	for(uint8_t i = 0; i < size; i++)
		serial_send(s[i]);
}
