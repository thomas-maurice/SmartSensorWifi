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
 * \file spi.c
 * \author Thomas Maurice
 * 
 * \brief SPI management
 * \version 0.1
 * 
 */

#include <spi.h>
#include <macros.h>
#include <util/delay.h>

void init_spi() {
	sbi(DDRB, PB5);
	sbi(DDRB, PB2);
	sbi(DDRB, PB3);
	sbi(DDRD, PD4);
	sbi(PORTD, PD4);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1) | (1<<SPR0);
}

uint8_t spi_send(uint8_t data) {
	cbi(PORTD, PD4);
	_delay_us(1);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	sbi(PORTD, PD4);
	_delay_us(1);
	return SPDR;
}

void display_send(uint8_t data) {
	spi_send(data);
}

void display_clear() {
	spi_send(0x76);
}
