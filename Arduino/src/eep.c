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
 * \file eep.c
 * \author Thomas Maurice
 * 
 * \brief EEPROM management 
 * \version 0.1
 * 
 */

#include <eep.h>

void eep_update_data(uint16_t addr, char* data, uint8_t len) {
	eeprom_update_word((uint16_t*)addr, len);
	eeprom_update_block(data, (void*)(addr+1), len);
}

uint8_t eep_read_data(uint16_t addr, char* data) {
	uint8_t l = eeprom_read_word((uint16_t*)addr);
	eeprom_read_block((void*)data, (void*)(addr+1), l);
	return l;
}
