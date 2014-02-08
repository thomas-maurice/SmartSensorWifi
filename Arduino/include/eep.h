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
 * \file eep.h
 * \author Thomas Maurice
 * 
 * \brief EEPROM management header 
 * \version 0.1
 * 
 */

#ifndef EEPROM_HEADER_
#define EEPROM_HEADER_

/**
 * Memory structure of the EEPROM
 * 0x000: Length of the ESSID
 * 0x001-0x049 ESSID
 * 0x050: Length of the password
 * 0x051-0x099: PASSWORD
 * 0x0A0: Length of the user
 * 0x00A1-0x0EF: USER
 */

/*
 * Each block will be this format :
 *  * one byte length
 *  * 49  bytes of data
 * 
 * So keys/essids/usernames up to 0x49 chars long can be stored
 * 
 * To store and read a string to memory, just do the following :
 * 
 * ~~~~~~~{.c}
 *  eep_update_data(EEP_ESSID, "foobar\n", 7);
 *	char s[50];
 *	uint8_t l = eep_read_data(EEP_ESSID, s);
 *	for(uint8_t i = 0; i < l; i++) {
 *		serial_send(s[i]);
 *	}
 * ~~~~~~~
 */
#define EEP_ESSID    0x000 //!< Address of the ESSID block
#define EEP_PASSWORD 0x050 //!< Address of the PASSWORD block
#define EEP_USERNAME 0x0A0 //!< Address of the USERNAME block

#define DATA_LENGTH 0x49

#include <avr/eeprom.h>
#include <avr/io.h>

void eep_update_data(uint16_t addr, char* data, uint8_t len);
uint8_t eep_read_data(uint16_t addr, char* data); 

#endif
