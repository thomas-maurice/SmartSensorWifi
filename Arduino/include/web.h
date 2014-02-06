#ifndef WEB_HEADER_
#define WEB_HEADER_

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <serial.h>
#include <adc.h>

#define MAX_REQUEST_LENGTH 24 //!< Maximum lenght of a request
char request[MAX_REQUEST_LENGTH+1]; //!< Request
int request_index; //!< Current position we are in the request

/** Sends a webpage with title and body */
void web_send_page(char* title, char* body);
/** Main web function, handles the request 'req' */
void web_parse_request(char* req, int size);

#endif
