#ifndef WIZNET210
#define WIZNET210

#include <avr/io.h>
#include <eep.h>

int wizFi210_check_ok();
void wizFi210_send_update();
char wizFi210_check_connect();
void wizFi210_send_data(char cid, char* data);
int wizFi210_get_next_command(char cid);
void wizFi210_login_to_network();

#endif
