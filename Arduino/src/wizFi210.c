#include <wizFi210.h>
#include <avr/io.h>
#include <serial.h>
#include <spi.h>

int wizFi210_check_ok() {
	for(uint8_t i = 0; i < WIZFI210_BUFSIZE-4; i++) {
		if(wizFi210_recv_buffer[i] == '[' && 
		   wizFi210_recv_buffer[i+1] == 'O' && 
		   wizFi210_recv_buffer[i+2] == 'K' && 
		   wizFi210_recv_buffer[i+3] == ']') {
			return 1;
		}
	}
	
	return 0;
}

void wizFi210_init() {
	memset(wizFi210_recv_buffer, 0, WIZFI210_BUFSIZE);
	wizFi210_recv_len = 0;
}
