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
 * \file wizfi210.h
 * \author Thomas Maurice
 * 
 * \brief wifi management header 
 * \version 0.1
 * 
 */

#ifndef WIZNET210
#define WIZNET210

#include <avr/io.h>
#include <eep.h>

int wizFi210_check_ok(); //!< Checks if the command is OK
void wizFi210_send_update(); //!< Send an update to the server
char wizFi210_check_connect(); //!< Checks for a client connection
void wizFi210_send_data(char cid, char* data); //!< Sends a data to a CID
int wizFi210_get_next_command(char cid); //!< Parse and axecute the next AT command
void wizFi210_login_to_network(); //!< Logs in to a network

#endif
