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
 * \file main.c
 * \author Thomas Maurice
 * 
 * \brief Main file of the Smart Sensor Wifi project
 * \version 0.1
 * 
 * This file demonstrates a simple HTTP serial server.
 * Optimized for an atmega8.
 */

#include <avr/io.h>
#include <avr/interrupt.h> 	
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include <adc.h>
#include <macros.h>
#include <web.h>
#include <serial.h>
#include <eep.h>
#include <ds1302.h>

// Json : '{"key":"value","key2":"value2"}'

/**
 * \brief Main function of the program
 * 
 * Will just perform the initializations of the chip, since
 * the whole thing is interrupt-driven.
 */
int main(void)
{
	// Peripherals inits
	serial_init();
	adc_init();
	
	// Register inits
	sbi(DDRB,PB5); // To blink the LED
	
	// Varialble inits
	request_index = 0;
	
	sei(); // Global interruption enable
	
	for(;;){
		_delay_ms(1000);
		uint8_t r = ds1302_read_register(0x00, DS1302_CLOCK_BYTE);
		//ds1302_write_byte(0x00, 0x07);
		serial_send(((r>>4)&0x7)+'0');
		serial_send((r&0x0f)+'0');
		serial_send('\n');
	}

	return 0;
}
