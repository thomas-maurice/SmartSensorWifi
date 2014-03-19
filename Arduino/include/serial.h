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
 * \file serial.h
 * \author Thomas Maurice
 * 
 * \brief serial management header 
 * \version 0.1
 * 
 */

#ifndef SERIAL_HEADER_
#define SERIAL_HEADER_

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

/** Baudrate for the serial link */
#define BAUDRATE	8 // value for 115200 //103 // UBRR value for 9600

/** Initializes the serial link for 9600 bauds */
void serial_init(void);
/** Sends a char to the serial port */
void serial_send(unsigned char c);
/** Sends a string to the serial port */
void serial_send_string(const char* s, int size);
void serial_send_string_nt(const char* s);

#endif
