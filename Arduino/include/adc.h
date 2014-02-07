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
 * \file adc.h
 * \author Thomas Maurice
 * 
 * \brief ADC management header 
 * \version 0.1
 * 
 */

#ifndef ADC_HEADER_
#define ADC_HEADER_

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <serial.h>

/** Initializes the ADC */
void adc_init();
/** Returns the value read on the channel 'channel' of the ADC */
uint8_t adc_get_sample(uint8_t channel);
/** Converts the value of the channel of the ADC into a char[4] */
void adc_to_char(int channel, char* str);
/** Sends the value of the channel 'channel' on the serial port */
void adc_print_conv(int channel);

#endif
