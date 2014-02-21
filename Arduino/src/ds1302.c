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

#include <ds1302.h>

/**
 * Initializes the data transfert between the RTC and the chip.
 * This will configure the DDR as well as the initial state of
 * the lines.
 */
void ds1302_init_transfert() {
	// Set CE low and as an output
	sbi(DS1302_CE_DDR, DS1302_CE_PIN);
	cbi(DS1302_CE_PORT, DS1302_CE_PIN);
	
	// Set the clock low and as an output
	sbi(DS1302_CLK_DDR, DS1302_CLK_PIN);
	cbi(DS1302_CLK_PORT, DS1302_CLK_PIN);
	
	// Finally start the transfert setting the CE high
	sbi(DS1302_CE_PORT, DS1302_CE_PIN);
	
	_delay_us(4);
}

/**
 * Closes all the data transfers. This will disable the RTC CE line.
 */
void ds1302_end_transfert() {
	// Finally end the transfert setting the CE low
	cbi(DS1302_CE_PORT, DS1302_CE_PIN);
	
	_delay_us(4);
}

/**
 * Shifts a byte to the RTC
 * 
 * \param [in] byte The byte to shift
 */
void ds1302_shift_byte(uint8_t byte) {
	for(uint8_t i = 0; i < 8; i++) {
		cbi(DS1302_IO_PORT, DS1302_IO_PIN);
		DS1302_IO_PORT |= (((gbi(byte,i))<<DS1302_IO_PIN));
		_delay_us(1);
		sbi(DS1302_CLK_PORT, DS1302_CLK_PIN);
		_delay_us(1);
		cbi(DS1302_CLK_PORT, DS1302_CLK_PIN);
		_delay_us(1);
	}
}

/**
 * This function will write to a register of the RTC. This function
 * can be user either to configure the chip or to use the general
 * purpose ram.
 * 
 * \param [in] addr The address to write
 * \param [in] value The value to write
 * \param [in] target The target. Is either the clock register or the RAM register.
 * This value has either DS1302_CLOCK_BYTE or DS1302_RAM_BYTE value.
 */
void ds1302_write_register(uint8_t addr, uint8_t value, uint8_t target) {
	ds1302_init_transfert();
	uint8_t cmd = 0x0;
	cmd |= 0x80 | target | DS1302_WRITE_BYTE; // We want to write
	cmd |= ((addr&0x1F) << 1); // Let's put the address
	
	// Now we shift out the whole thing
	ds1302_shift_byte(cmd);
	ds1302_shift_byte(value);
	
	ds1302_end_transfert();
}

/**
 * Read the value stored in a register of the chip and returns it. This
 * function can be user either to read the chip or to use the general
 * purpose ram.
 * 
 * \param [in] addr The address to read
 * \param [in] target The target. Is either the clock register or the RAM register.
 * This value has either DS1302_CLOCK_BYTE or DS1302_RAM_BYTE value.
 * 
 * \return The value read
 */
uint8_t ds1302_read_register(uint8_t addr, uint8_t target) {
	ds1302_init_transfert();
	uint8_t cmd = 0x0;
	cmd |= 0x80 | DS1302_CLOCK_BYTE | DS1302_READ_BYTE; // We want to read from the clock
	cmd |= ((addr) << 1); // Let's put the address
	uint8_t res = 0x0;
	
	// Put the I/O line to output
	sbi(DS1302_IO_DDR, DS1302_IO_PIN);
	
	// Now we shift out the whole thing
	ds1302_shift_byte(cmd);
	
	// Put IO line to input & disable pull up
	cbi(DS1302_IO_DDR, DS1302_IO_PIN);
	cbi(DS1302_IO_PORT, DS1302_IO_PIN);
	
	for(uint8_t i = 0; i < 8; i++) {
		res |= (gbi(DS1302_IO_RD_PORT, DS1302_IO_PIN)<<i);
		
		_delay_us(1);
		sbi(DS1302_CLK_PORT, DS1302_CLK_PIN);
		_delay_us(1);
		cbi(DS1302_CLK_PORT, DS1302_CLK_PIN);
		_delay_us(1);
	}
	
	// Restore the I/O line to output
	sbi(DS1302_IO_DDR, DS1302_IO_PIN);
	cbi(DS1302_IO_PORT, DS1302_IO_PIN);
	
	ds1302_end_transfert();
	
	return res;
}