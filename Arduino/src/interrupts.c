/**
 * \file interrupts.c
 * \author Thomas Maurice
 * 
 * \brief All the interrupts go there
 * \version 0.1
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h> 	
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include <web.h>
#include <serial.h>
#include <adc.h>

ISR(USART_RX_vect) {
	char recv = UDR0;
	if(recv != '\n') {
		request[request_index] = recv;
		request[request_index+1] = '\0';
		if(request_index == MAX_REQUEST_LENGTH) {
			web_parse_request(request, request_index+1);
			request_index = 0;
		}
		request_index = request_index + 1;
	} else {
		web_parse_request(request, request_index+1);
		request_index = 0;
	}
}
