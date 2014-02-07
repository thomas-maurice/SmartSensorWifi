/*
 *
 *	Copyright (C) 2014 Thomas MAURICE <tmaurice59@gmail.com>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License along
 *	with this program; if not, write to the Free Software Foundation, Inc.,
 *	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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

void serial_send_string(const char* s, int size) {
	for(uint8_t i = 0; i < size; i++)
		serial_send(s[i]);
}
