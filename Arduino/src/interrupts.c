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
 * \file interrupts.c
 * \author Thomas Maurice
 * 
 * \brief All the interrupts go there
 * \version 0.1
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h> 	
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include <macros.h>

#include <serial.h>
#include <adc.h>
#include <spi.h>
#include <wizFi210.h>

/**
 * \brief USART RX Interrupt
 * 
 * This will handle all the serial communication
 * recieved by the board. For now this  is  used
 * to handle the HTTP requests sent to the board
 */
ISR(USART_RX_vect) {
	
}

ISR(TIMER1_COMPA_vect) {
	static uint16_t cpt = 0; // == 30 every second
	static uint16_t seconds = 0;
	static uint16_t minutes = 0;  
	static uint8_t state = 0;
	cpt++;
	if(cpt==61) {
		cpt = 0;
		seconds++;
		if(seconds == 60) {
			minutes++;
			seconds = 0;
		}
		
		if(minutes == 1) {
			minutes = 0;
			_delay_ms(500);
			serial_send_string_nt("+++");
			_delay_ms(500);
			_delay_ms(2000);
			sbi(PORTB, PB2);
			wizFi210_send_update();
			cbi(PORTB, PB2);
			_delay_ms(500);
		}
	
	}
}
