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
 * \file spi.h
 * \author Thomas Maurice
 * 
 * \brief SPI management header 
 * \version 0.1
 * 
 */

#ifndef SPI_HEADER_
#define SPI_HEADER_

#include <avr/io.h>
#include <util/delay.h>
#include <serial.h>
/*
#define SPI_ESC_CHAR 0xFB // Start transmission indication 
#define SPI_IDLE_CHAR 0xF5 // synchronous IDLE 
#define SPI_XOFF_CHAR 0xFA // Stop transmission indication 
#define SPI_XON_CHAR 0xFD // Start transmission indication 
#define SPI_INVALID_CHAR_ALL_ONE 0xFF// Invalid character possibly recieved during reboot 
#define SPI_INVALID_CHAR_ALL_ZERO 0x00 // Invalid character possibly recieved during reboot 
#define SPI_LINK_READY 0xF3

void init_spi(); //!< Initializes the SPI port
uint8_t spi_send(uint8_t data); //!< Sends/retrieves data
uint8_t spi_byte_stuff(uint8_t c);
void spi_send_buffer(unsigned char* buf);
*/

void init_spi(); //!< Initializes the SPI port
uint8_t spi_send(uint8_t data); //!< Sends/retrieves data
void display_send(uint8_t data);
void display_clear();

#endif
