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
 * \file ds1302.c
 * \author Thomas Maurice
 * 
 * \brief Implements an interface to the DS1302 RTC chip
 * \version 0.1
 * 
 */
 
#ifndef DS1302_HEADER_
#define DS1302_HEADER_

#include <avr/io.h>
#include <util/delay.h>
#include <macros.h>

/*
 * Device configuration
 */
#define DS1302_CE_PORT    PORTD //!< Chip select port
#define DS1302_CE_PIN     PD7   //!< Chip select pin
#define DS1302_CE_DDR     DDRD  //!< Chip select data direction register

#define DS1302_IO_PORT    PORTB //!< I/O line port
#define DS1302_IO_PIN     PB0   //!< I/O line pin
#define DS1302_IO_DDR     DDRB  //!< I/O line data direction register
#define DS1302_IO_RD_PORT PINB  //!< I/O line data read port

#define DS1302_CLK_PORT   PORTB //!< Clock port
#define DS1302_CLK_PIN    PB1   //!< Clock pin
#define DS1302_CLK_DDR    DDRB  //!< Clock data direction register

/*
 * Basic I/O operations
 * 
 * A command/address byte has the following format :
 * MSB:7, LSB:0
 * 7: Logic 1
 * 6: RAM data (1)/ Clock data (0)
 * 5: A/C4 Address bit 4
 * 4: A/C3 Address bit 3
 * 3: A/C2 Address bit 2
 * 2: A/C1 Address bit 1
 * 1: 1/C0 Address bit 0 
 * 0: R/W Read: 1, Write 0
 * 
 * The data are output LSB first.
 */
#define DS1302_READ_BYTE  0x1
#define DS1302_WRITE_BYTE 0x0
#define DS1302_RAM_BYTE   0x40
#define DS1302_CLOCK_BYTE 0x00

void ds1302_init_transfert();
void ds1302_end_transfert();
void ds1302_shift_byte(uint8_t byte);
void ds1302_write_register(uint8_t addr, uint8_t value, uint8_t target);
uint8_t ds1302_read_register(uint8_t addr, uint8_t target);

#endif
