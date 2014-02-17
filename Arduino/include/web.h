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
 * \file web.h
 * \author Thomas Maurice
 * 
 * \brief web management header 
 * \version 0.1
 * 
 */

#ifndef WEB_HEADER_
#define WEB_HEADER_

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <serial.h>
#include <adc.h>
#include <eep.h>

#define MAX_REQUEST_LENGTH 0x40 //!< Maximum lenght of a request
char request[MAX_REQUEST_LENGTH+1]; //!< Request
int request_index; //!< Current position we are in the request

/** Sends a webpage with title and body */
void web_send_page(char* title, char* body);
/** Main web function, handles the request 'req' */
void web_parse_request(char* req, int size);

#endif
