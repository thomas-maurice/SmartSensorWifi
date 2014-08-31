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
 * \file strops.c
 * \author Thomas Maurice
 * \version 0.1
 * 
 * Some code
 */

#include <strops.h>

void int_to_str(uint8_t c, unsigned char* str) {
	str[0] = (c/100)+48;
	str[1] = (c/10)%10+48;
	str[2] = c%10+48;
	str[3] = '\0';
}

void int_to_hex_str(uint8_t c, unsigned char* str) {
	str[0] = '0';
	str[1] = 'x';
	str[2] = (c/16);
	(str[2] < 10) ? (str[2] += '0') : (str[2] += 'A');
	str[3] = (c%16);
	(str[3] < 10) ? (str[3] += '0') : (str[3] += 'A');
	str[4] = '\0';
}
