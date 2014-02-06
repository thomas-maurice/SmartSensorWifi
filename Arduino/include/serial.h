#ifndef SERIAL_HEADER_
#define SERIAL_HEADER_

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

/** Baudrate for the serial link */
#define BAUDRATE	103 // UBRR value for 9600

/** Initializes the serial link for 9600 bauds */
void serial_init(void);
/** Sends a char to the serial port */
void serial_send(unsigned char c);
/** Sends a string to the serial port */
void serial_send_string(char* s, int size);

#endif
