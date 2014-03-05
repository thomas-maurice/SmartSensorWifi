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
 * \file ds1302.h
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
 * Macros
 */
 
#ifndef sbi
/** Sets a bit */
#define sbi(port, bit) port |= (1<<(bit))
#endif
#ifndef cbi
/** Clears a bit */
#define cbi(port, bit) port &= ~(1<<(bit))
#endif
#ifndef gbi
/** Gets a bit */
#define gbi(port, bit) ((port&(1<<bit))>>bit)
#endif
/** Converts a decimal value to a BCD one */
#define dec_to_bcd(val) (((val)/10)*16+((val)%10))
/** Converts a BCD value to a dedimal one */
#define bcd_to_dec(val) ((((val)&0xF0)>>4)*10+((val)&0x0F))

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
#define DS1302_RAM        0x40
#define DS1302_CLOCK      0x00

#define DS1302_SECONDS 0x00
#define DS1302_MINUTES 0x01
#define DS1302_HOURS   0x02
#define DS1302_DATE    0x03
#define DS1302_MONTH   0x04
#define DS1302_YEAR    0x06
#define DS1302_WP      0x07

void ds1302_init_transfert(); //!< Initializes a data transfert
void ds1302_end_transfert(); //!< Ends a data transfert 
void ds1302_shift_byte(uint8_t byte); //!< Shifts a byte to the IO line
void ds1302_write_register(uint8_t addr, uint8_t value, uint8_t target); //!< Writes to a register
uint8_t ds1302_read_register(uint8_t addr, uint8_t target); //!< Reads from a register
void get_time_string(char* time_string); //!< Creates a time string with the format "DD/MM/YY HH:MM:SS"
void ds1302_clear_write_protect(); //!< Clears the WP byte. This will  enable the write to the chip.
void ds1302_clear_clock_halt(); //!< This clears the Clock Halt bit, this will allow the clock to start
void ds1302_set_date(uint8_t day, uint8_t month, uint16_t year); //!< Changes the date
void ds1302_set_time(uint8_t hrs, uint8_t mins, uint8_t secs); //!< Changes the time

#endif
