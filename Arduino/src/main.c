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

/**
 * \mainpage Smart sensor WiFi
 * 
 * # Introduction
 * 
 * This project is a student project managed by Polytech Lille Engineering
 * School. It is led by two students, *Thomas Maurice* and *Benoit Maliar*. Both
 * students in 4th year.
 * 
 * The aim of the project is to create a distributed WiFi sensor network
 * that is able to regularly communicate various data to a central DB and
 * autoreconfigure itself in order to be energy efficient.
 * 
 * This part of the project is the microcontroller part of the project. The
 * main components used are an atmega328p, a DS1302 real time clock and a
 * WizFi210 WiFi chip.
 * 
 * Note that the project is open source and you can modify it. Especially
 * the drivers for the RTC and the WiFi chip, you are more than welcome to
 * study and improve them.
 * 
 * # Compiling
 * 
 * To compile the project you just need AVR-gcc installed. Just go in the
 * `Arduino` directory and run `make`. Everything will compile well. If
 * not, just undo your changes to my code !
 * 
 * It will create a nice .hex for upload. If your target is an Arduino board
 * then just type `make flash` to upload it using the built-in bootloader.
 * If it is just a bare-metal atmega328p then wire it up to your USBASP
 * device and run avrdude with the good options.
 * 
 * Have fun :)
 */

// CS de la carte wifi : PD6
// CS de la flash : PD5

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
#include <spi.h>
#include <wizFi210.h>

// Json : '{"key":"value","key2":"value2"}'
static char buf[7];
int check_ok() {

	int stop = 0;
	
	while(stop==0) {
		while(!(UCSR0A&(1<<RXC0)));
		char c = UDR0;
		if(c=='\n')
			continue;
		if(c=='\r')
			continue;
		for(int i = 0; i < 7; i++) {
			buf[i] = buf[i+1];
		}
		
		buf[6] = c;
		
		/*serial_send_string(buf, 7);
		serial_send('|');
		serial_send('\n');
		*/
		if(strncmp(buf, "[ERROR:", 7) == 0) {
			return 1;
		}
		else if(strncmp(buf+3, "[OK]", 4) == 0) {
			return 0;
		}
	}
}

/**
 * \brief Main function of the program
 * 
 * Will just perform the initializations of the chip, since
 * the whole thing is interrupt-driven.
 */
int main(void)
{
	wizFi210_init();
	
	// Peripherals inits
	serial_init();
	adc_init();
	init_spi();
	
	// Register inits
	sbi(DDRB,PB5); // To blink the LED L
	
	// Varialble inits
	request_index = 0;
	
	sei(); // Global interruption enable
	
	// Let's enable the clock !
	ds1302_clear_write_protect();
	ds1302_clear_clock_halt();
	
	ds1302_set_date(5, 3, 2014);
	
	display_clear();
	cli();
	serial_send_string_nt("\rAT+WM=0\r");
	_delay_ms(10);
	if(check_ok() == 0) {
		serial_send_string_nt("OKTAMERE\r");
		if(check_ok() == 1)
			serial_send_string_nt("ERR\r");
		sei();
	}
	serial_send_string_nt("AT+NDHCP=0\r");
	serial_send_string_nt("AT+WSEC=8\r");
	serial_send_string_nt("AT+WPAPSK=Network,lolimagonnagiveyouthepassword\r");
	//serial_send_string_nt("AT+WPSK=pas facile a retenir, hein ?\r");
	serial_send_string_nt("AT+WA=PolyWSN\r");
	serial_send_string_nt("AT+NSET=172.26.240.13,255.255.255.0,172.26.240.254\r");
	//_delay_ms(1000);
	//serial_send_string_nt("AT+PING=172.26.240.254,1\r");
	//_delay_ms(1000);
	//serial_send_string_nt("AT+WS\r");
	serial_send_string_nt("AT+NCTCP=193.48.57.56,80\r");
	_delay_ms(5000);
	serial_send_string_nt("AT+CID=?\r");
	_delay_ms(1000);
	serial_send(0x1B);
	serial_send_string_nt("S0");
	serial_send_string_nt("POST /recup.php HTTP/1.0\n\
Host: smartsensorwifi.plil.net\n\
Content-type: application/x-www-form-urlencoded\n\
Content-length: 40\n\
\n\
temp=240&lum=140&mid=42&mpass=captest\n         ");
	serial_send(0x1B);
	serial_send('E');
	
	for(;;){
		_delay_ms(1000);
		sbi(PORTB, PB3);
		/*char date[17];
		get_time_string(date);
		serial_send_string(date, 17);
		serial_send('\n');
		*/
		cbi(PORTB, PB3);
	}

	return 0;
}
