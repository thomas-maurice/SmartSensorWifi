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
 * \file web.c
 * \author Thomas Maurice
 * 
 * \brief Web management file
 * \version 0.1
 * 
 */

#include <web.h>

void web_send_page(char* title, char* body) {
	char *status = "HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\n\n";
	serial_send_string(status, strlen(status));
	
	char *head = "<html><head><title>";
	serial_send_string(head, strlen(head));
	serial_send_string(title, strlen(title));
	char *prebody = "</title></head>\r\n<body>";
	serial_send_string(prebody, strlen(prebody));
	serial_send_string(body, strlen(body));
	char *foot = "</body></html>\r\n";
	serial_send_string(foot, strlen(foot));
	
}

void web_parse_request(char* req, int size) {
	char getstr[3];
	char getstr2[3];
	//send_serial_string(req, size);
	char page[MAX_REQUEST_LENGTH-4] = {'\0'}; // Because len("GET ") = 4
	strncpy(getstr, req, 3);

	if(strncmp(getstr, "GET", 3) == 0) {
		// Process the get request.
		int i = 4;
		while(i < size || req[i] == ' ') {
			page[i-4] = req[i];
			i++;
		}

		if(strcmp(page, "/") == 0) {
			web_send_page("Index", "No content yet :)");
		} else if(strcmp(page, "/temp")==0) {
			char t[4];
			adc_to_char(0, t);
			web_send_page("Temperature", t);
		} else {
			web_send_page("Error", "Not a valid page");
		}
	} else {
		// Not a GET request, or garbage, ignoring
	}
}
