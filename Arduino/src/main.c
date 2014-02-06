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
