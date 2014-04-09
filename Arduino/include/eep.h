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
 *  * Between 1 and EEP_MAX_DATA_LENGTH bytes of data
 * 
 * So keys/essids/usernames up to EEP_MAX_DATA_LENGTH chars
 * long can be stored.
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

#define EEP_MAX_DATA_LENGTH 0x20 //!< Maximum value is 0xFF !
#define EEP_ID       (0x000) //!< ID
#define EEP_PASSWORD (EEP_ID+1+20) //!< Password
#define EEP_ESSID    (EEP_PASSWORD+1+0x20) //!< ESSID
#define EEP_NETPASS  (EEP_ESSID+1+0x20) //!< Network key
#define EEP_NETTYPE  (EEP_NETPASS+1+0x20) //!< Network type
#define EEP_DHCP     (EEP_NETTYPE+1+2) //!< DHCP
#define EEP_NETIP    (EEP_DHCP+1+2) //!< Network config
#define EEP_NETMSK   (EEP_NETIP+1+16) //!< Network config
#define EEP_NETGW    (EEP_NETMSK+1+16) //!< Network config
#define EEP_MASTER   (EEP_NETGW+1+16) //!< MasterKey
#define EEP_IPDB     (EEP_MASTER+1+32) //!< IP of the db server
#define EEP_HOSTDB   (EEP_IPDB+1+16) //!< hostname of the DB server

#include <avr/eeprom.h>
#include <avr/io.h>

/** Updates a sector in EEPROM */
void eep_update_data(uint16_t addr, char* data, uint8_t len);
/** Reads a sector in EEPROM */
uint8_t eep_read_data(uint16_t addr, char* data); 

#endif
