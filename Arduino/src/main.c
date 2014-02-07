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
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include <adc.h>
#include <web.h>
#include <serial.h>
#include <eep.h>

// Json : '{"key":"value","key2":"value2"}'

/**
 * \brief Main function of the program
 */
int main(void)
{
	serial_init();
	adc_init();
	
	request_index = 0;
	
	sei();
	
	for(;;){
		_delay_ms(1000);
	}

	return 0;
}
