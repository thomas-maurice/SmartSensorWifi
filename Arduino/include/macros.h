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
 * \file macros.h
 * \author Thomas Maurice
 * 
 * \brief Miscellaneaous macros
 * \version 0.1
 * 
 */
 
#ifndef MACROS_HEADER_
#define MACROS_HEADER_

/** Sets a bit */
#define sbi(port, bit) port |= (1<<(bit))
/** Clears a bit */
#define cbi(port, bit) port &= ~(1<<(bit))

#endif
