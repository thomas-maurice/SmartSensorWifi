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
 * \file wizfi210.c
 * \author Thomas Maurice
 * 
 * \brief wifi management implementation 
 * \version 0.1
 * 
 */

#include <wizFi210.h>
#include <avr/io.h>
#include <serial.h>
#include <adc.h>
#include <spi.h>
#include <avr/interrupt.h>

/** Static buffer used to check wether it's an error or not */
static char buf[7];
/**
 * Loops through the infomming data flow till it encounters a [OK] ar an
 * [ERROR: string.
 * 
 * \return 0 if OK and 1 if ERROR
 */
int wizFi210_check_ok() {

	int stop = 0;
	
	while(stop==0) {
		while(!(UCSR0A&(1<<RXC0)));
		char c = UDR0;
		if(c=='\n')
			continue;
		if(c=='\r')
			continue;
		for(int i = 0; i < 7; i++) {
			buf[i] = buf[i+1];
		}
		
		buf[6] = c;
		
		/*serial_send_string(buf, 7);
		serial_send('|');
		serial_send('\n');
		*/
		if(strncmp(buf+1, "[ERROR", 6) == 0) {
			return 1;
		}
		else if(strncmp(buf+3, "[OK]", 4) == 0) {
			return 0;
		}
	}
}

/** Static buffer used to store the flow */
static char bufconnect[12];
/**
 * Loops until someone connects to the sensor
 * 
 * \return The matching CID in a char format
 */
char wizFi210_check_connect() {

	int stop = 0;
	
	while(stop==0) {
		while(!(UCSR0A&(1<<RXC0)));
		char c = UDR0;
		if(c=='\n')
			continue;
		if(c=='\r')
			continue;
		for(int i = 0; i < 12; i++) {
			bufconnect[i] = bufconnect[i+1];
		}
		
		bufconnect[11] = c;
		
		if(strncmp(bufconnect, "[CONNECT ", 9) == 0) {
			return bufconnect[11];
		}
	}
}

/**
 * This will send the data data to the giver connection ID. It will
 * wrap the data between all the good special chars :)
 * 
 * \param [in] cid The connection ID you want to use
 * \param [in] data the data you want to send
 */
void wizFi210_send_data(char cid, char* data) {
	serial_send('\r');
	serial_send(0x1B);
	serial_send('S');
	serial_send(cid);
	serial_send_string_nt(data);
	serial_send(0x1B);
	serial_send('E');
	serial_send('\r');
}

/**
 * Read and execute the next command on the giver CID.
 * If a command can be executed it will print [OK] to the client, [FAIL]
 * otherwise.
 * 
 * Note that this function works with the serial port as welll as with
 * any network connection.
 * 
 * \return 0 if next command is ready to be waited for and processed. 1 if the
 * client disconnected.
 */
int wizFi210_get_next_command(char cid) {
	unsigned char buffer[128];
	memset(buffer, '\0', 128);
	unsigned char ok[2];
	ok[0] = 0x1B;
	ok[1] = 'O';
	int stop = 0;
	int n = 0;
	while(stop==0 && n < 128) {
		while(!(UCSR0A&(1<<RXC0)));
		char c = UDR0;
		
		if(c=='\r' || c=='\n') {
			if(n < 6) {
				continue;
			}
			stop = 1;
			continue;
		}
			
		buffer[n] = c;
		char* p = strstr(buffer, ok);
		if(p != NULL) {n=0;continue;}
		n++;
	}
	
	char* ptr = strstr(buffer, "AT+IDENT");
	if(ptr != NULL) {
		unsigned char data[64];
		int len=0;
		
		len=eep_read_data(EEP_MASTER, data);
		if(strncmp(data, ptr+9, len)==0)
			wizFi210_send_data(cid, "[OK]\r\n");
		else
			wizFi210_send_data(cid, "[FAIL] Invalid ident\r\n");
		
		return 0;
	}
	
	ptr = strstr(buffer, "AT+IP=");
	if(ptr != NULL) {
		wizFi210_send_data(cid, ptr+6);
		return 0;
	}
	ptr = strstr(buffer, "AT+DUMP");
	if(ptr != NULL) {
		unsigned char data[64];
		int len=0;
		memset(data, '\0', 64);
		serial_send('\r');
		serial_send(0x1B);
		serial_send('S');
		serial_send(cid);
		
		len=eep_read_data(EEP_DHCP, data);
		serial_send_string_nt("\r\nAT+DHCP=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_ID, data);
		serial_send_string_nt("\r\nAT+ID=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_PASSWORD, data);
		serial_send_string_nt("\r\nAT+PW=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_ESSID, data);
		serial_send_string_nt("\r\nAT+ESSID=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_NETPASS, data);
		serial_send_string_nt("\r\nAT+WKEY=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_NETTYPE, data);
		serial_send_string_nt("\r\nAT+NETTYPE=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_NETIP, data);
		serial_send_string_nt("\r\nAT+NIP=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_NETGW, data);
		serial_send_string_nt("\r\nAT+NGW=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_NETMSK, data);
		serial_send_string_nt("\r\nAT+NMSK=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_MASTER, data);
		serial_send_string_nt("\r\nAT+MASTER=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_IPDB, data);
		serial_send_string_nt("\r\nAT+IPDB=");
		serial_send_string(data, len);
		
		len=eep_read_data(EEP_HOSTDB, data);
		serial_send_string_nt("\r\nAT+HOSTDB=");
		serial_send_string(data, len);
		
		serial_send_string_nt("\r\nAT+DONE\r\n");
		
		serial_send(0x1B);
		serial_send('E');
		serial_send('\r');
		return 0;
	}
	ptr = strstr(buffer, "AT+ID=");
	if(ptr != NULL) {
		eep_update_data(EEP_ID, ptr+6, strlen(ptr+6));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+PW=");
	if(ptr != NULL) {
		eep_update_data(EEP_PASSWORD, ptr+6, strlen(ptr+6));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+DHCP=");
	if(ptr != NULL) {
		eep_update_data(EEP_DHCP, ptr+8, strlen(ptr+8));
		wizFi210_send_data(cid, ptr+8);
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+NIP=");
	if(ptr != NULL) {
		eep_update_data(EEP_NETIP, ptr+7, strlen(ptr+7));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+NMSK=");
	if(ptr != NULL) {
		eep_update_data(EEP_NETMSK, ptr+8, strlen(ptr+8));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+MASTER=");
	if(ptr != NULL) {
		eep_update_data(EEP_MASTER, ptr+10, strlen(ptr+10));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+NGW=");
	if(ptr != NULL) {
		eep_update_data(EEP_NETGW, ptr+7, strlen(ptr+7));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+NETTYPE=");
	if(ptr != NULL) {
		eep_update_data(EEP_NETTYPE, ptr+11, strlen(ptr+11));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+EXIT");
	if(ptr != NULL) {
		wizFi210_send_data(cid, "[OK] EXITING CONFIG MODE\r\n");
		return 1;
	}
	ptr = strstr(buffer, "AT+ESSID=");
	if(ptr != NULL) {
		eep_update_data(EEP_ESSID, ptr+9, strlen(ptr+9));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+WKEY=");
	if(ptr != NULL) {
		eep_update_data(EEP_NETPASS, ptr+8, strlen(ptr+8));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+IPDB=");
	if(ptr != NULL) {
		eep_update_data(EEP_IPDB, ptr+8, strlen(ptr+8));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "AT+HOSTDB=");
	if(ptr != NULL) {
		eep_update_data(EEP_HOSTDB, ptr+10, strlen(ptr+10));
		wizFi210_send_data(cid, "[OK]\r\n");
		return 0;
	}
	ptr = strstr(buffer, "[ERROR");
	if(ptr != NULL)
		return 0;
	wizFi210_send_data(cid, "[FAIL]\r\n");
	return 0;
}

/**
 * Loads the parameters in EEPROM and connects to the given network.
 */
int wizFi210_login_to_network() {
	unsigned char data[64];
	int tries = 5;
	int res;
	int useDHCP;
	uint8_t len=0;
	uint8_t essidlen=0;
	unsigned char essid[32];
	
	cli();
	
	do {
		serial_send_string_nt("\rAT+WM=0\r");
		res = wizFi210_check_ok();
		tries--;
	} while (res != 0 && tries > 0);
	
	if(res != 0) { sei(); return 1;}
	
	tries = 5;
	
	memset(data, '\0', 64);
	memset(essid, '\0', 32);
	eep_read_data(EEP_DHCP, data);
	
	if(data[0] == '1') useDHCP = 1;
	else useDHCP = 0;

	do {
		serial_send_string_nt("AT+NDHCP=");
		serial_send('0');
		serial_send('\r');
		res = wizFi210_check_ok();
		tries--;
	} while (res != 0 && tries > 0);
	
	if(res != 0) { sei(); return 1;}
	
	tries = 5;
	
	memset(data, '\0', 64);
	eep_read_data(EEP_NETTYPE, data);
	unsigned char wsec = data[0];
	
	do {
		serial_send_string_nt("AT+WSEC=");
		serial_send(data[0]);
		serial_send('\r');
		
		res = wizFi210_check_ok();
		tries--;
	} while (res != 0 && tries > 0);
	
	if(res != 0) { sei(); return 1;}
	
	tries = 5;
	
	memset(data, '\0', 64);
	essidlen=eep_read_data(EEP_ESSID, essid);
	len=eep_read_data(EEP_NETPASS, data);
	
	do {
		switch(wsec) {
			case '8':
				serial_send_string_nt("AT+WPAPSK=");
				serial_send_string(essid, essidlen);
				serial_send(',');
				serial_send_string(data, len);
				serial_send('\r');
				break;
			case '4':
				serial_send_string_nt("AT+WWPA=");
				serial_send_string(data, len);
				serial_send('\r');
				break;
			case '2':
				serial_send_string_nt("AT+WWEP0=");
				serial_send_string(data, len);
				serial_send('\r');
				break;
				
		}
		
		res = wizFi210_check_ok();
		tries--;
	} while (res != 0 && tries > 0);
	
	if(res != 0) { sei(); return 1;}
	
	tries = 5;
	
	do {
		serial_send_string_nt("AT+WA=");
		serial_send_string(essid, essidlen);
		serial_send('\r');
		res = wizFi210_check_ok();
		tries--;
	} while (res != 0 && tries > 0);
	
	if(res != 0) { sei(); return 1;}
	
	tries = 5;
	
	if(useDHCP == 0) {
		do {
			serial_send_string_nt("AT+NSET=");
			len=eep_read_data(EEP_NETIP, data);
			serial_send_string(data, len);
			serial_send(',');
			len=eep_read_data(EEP_NETMSK, data);
			serial_send_string(data, len);
			serial_send(',');
			len=eep_read_data(EEP_NETGW, data);
			serial_send_string(data, len);
			serial_send('\r');
			
			res = wizFi210_check_ok();
			tries--;
		} while (res != 0 && tries > 0);
		
		if(res != 0) { sei(); return 1;}
	}
	
	sei();
}

/**
 * Send an update to the server.
 */
void wizFi210_send_update() {
	cli();
	
	int tries = 5;
	char data[64];
	
	memset(data, '\0', 64);
	int len=eep_read_data(EEP_IPDB, data);
	
	int res;
	do {
		serial_send_string_nt("AT+NCTCP=");
		serial_send_string(data, len);
		serial_send_string_nt(",80\r\r");
		res = wizFi210_check_ok();
		tries--;
		_delay_ms(1000);
	} while (res != 0 && tries > 0);
	
	serial_send_string_nt("\rAT+CID=?\r");
	_delay_ms(500);
	
	memset(data, '\0', 64);
	len=eep_read_data(EEP_HOSTDB, data);
	
	serial_send(0x1B);
	serial_send_string_nt("S1");
	serial_send_string_nt("POST /recup.php HTTP/1.0\nHost: ");
	serial_send_string(data, len);
	serial_send_string_nt("\n\
Content-type: application/x-www-form-urlencoded\n\
Content-length: 100\n\
\n\
temp=");
	char mesure[4];
	adc_to_char(0, mesure); // Temp
	serial_send_string_nt(mesure);
	serial_send_string_nt("&lum=");
	adc_to_char(1, mesure); // Lum
	serial_send_string_nt(mesure);
	serial_send_string_nt("&mid=");

	memset(data, '\0', 64);
	len = eep_read_data(EEP_ID, data);
	serial_send_string_nt(data);
	serial_send_string_nt("&mpass=");
	memset(data, '\0', 64);
	len = eep_read_data(EEP_PASSWORD, data);
	serial_send_string_nt(data);
	serial_send_string_nt("\n");
	for(int i = 0; i < 100; i++)
		serial_send(' ');
	serial_send(0x1B);
	serial_send('E');
	
	sei();
	
	return;
}
