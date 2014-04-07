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
 * \file interrupts.c
 * \author Thomas Maurice
 * 
 * \brief All the interrupts go there
 * \version 0.1
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h> 	
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include <serial.h>
#include <adc.h>
#include <spi.h>
#include <wizFi210.h>

/**
 * \brief USART RX Interrupt
 * 
 * This will handle all the serial communication
 * recieved by the board. For now this  is  used
 * to handle the HTTP requests sent to the board
 */
ISR(USART_RX_vect) {
	
}
