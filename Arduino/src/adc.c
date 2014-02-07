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
 * \file adc.c
 * \author Thomas Maurice
 * 
 * \brief ADC management file
 * \version 0.1
 * 
 */

#include <adc.h>

void adc_init() {
	ADMUX=(1<<REFS0)|(1<<ADLAR);
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint8_t adc_get_sample(uint8_t channel) {
	ADMUX=(ADMUX&0xF0)|channel;
	ADCSRA|=(1<<ADSC);
	while((ADCSRA&(1<<ADSC))!=0);
	return ADCH; // High part of the conversion. 2 LSB omitted
}

void adc_to_char(int channel, char* str) {
	int c = adc_get_sample(channel);
	str[0] = (c/100)+48;
	str[1] = (c/10)%10+48;
	str[2] = c%10+48;
	str[3] = '\0';
}

void adc_print_conv(int channel) {
	char s[4];
	adc_to_char(0, s);
	serial_send_string(s, strlen(s));
	serial_send_string("\r\n", 2);
}
