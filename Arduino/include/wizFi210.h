#ifndef WIZNET210
#define WIZNET210

#include <avr/io.h>

#define WIZFI210_BUFSIZE 128

uint8_t wizFi210_recv_buffer[WIZFI210_BUFSIZE];
uint8_t wizFi210_recv_len;

void wizFi210_init();
int wizFi210_check_ok();
uint8_t serial_recieve();
void wizFi210_associate(char* ap);

#endif
