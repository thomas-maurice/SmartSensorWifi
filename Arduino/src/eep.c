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

/**
 * This function will store the data block data in eeprom, starting from
 * the address addr+1, the length len of data will be stored at addr. So
 * obviously the length of the data shall not exceed 255. It also must be
 * strictly inferior to EEP_MAX_DATA_LENGTH in order to avoid overlapping
 * the data written in other memory sectors.
 * 
 * \param addr [in] The address at which we want to write data.
 * \param data [in] The data to write.
 * \param len  [in] The length of the memory block.
 */
void eep_update_data(uint16_t addr, char* data, uint8_t len) {
	if(len > EEP_MAX_DATA_LENGTH) len=EEP_MAX_DATA_LENGTH-1;
	eeprom_update_word((uint16_t*)addr, len);
	eeprom_update_block(data, (void*)(addr+1), len);
}

/**
 * This will read data contain at (addr+1) and put
 * n bytes in data. n is the value contained in the
 * address addr of the EEPROM. If nothing is found
 * e.g. value in addr is null, the function will set
 * data[0] to '\0' and return 0.
 * 
 * \param addr [in] the addr at which the memory block begins
 * \param data [out] The output data. Must be of size EEP_MAX_DATA_LENGTH
 * 
 * \return The number of byte that the function put into data
 */
uint8_t eep_read_data(uint16_t addr, char* data) {
	uint8_t l = eeprom_read_word((uint16_t*)addr);
	if(l == 0) {
		data[0] = '\0';
		return 0;
	}
	eeprom_read_block((void*)data, (void*)(addr+1), l);
	return l;
}
