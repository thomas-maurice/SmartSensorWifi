#include <wizFi210.h>
#include <avr/io.h>
#include <serial.h>
#include <spi.h>

int wizFi210_check_ok() {
	int stop = 0;
	static char buf[7];
	while(stop==0) {
		while(!(UCSR0A&(1<<RXC0)));
		char c = UDR0;
		for(int i = 0; i < 6; i++) {
			buf[i] = buf[i+1];
		}
		buf[6] = c;
		if(strncmp(buf, "[ERROR:", 7) == 0) {
			return 1;
		}
		else if(strncmp(buf+3, "[OK]", 4) == 0) {
			return 0;
		}
	}
}

void wizFi210_associate(char* ap) {
	serial_send_string_nt("AT+WA=");
	serial_send_string_nt(ap);
	serial_send_string_nt("\r");
}

void wizFi210_init() {
	memset(wizFi210_recv_buffer, 0, WIZFI210_BUFSIZE);
	wizFi210_recv_len = 0;
}

uint8_t serial_recieve() {
	while (!(UCSR0A & (1<<RXC0)))
	return UDR0;
}
