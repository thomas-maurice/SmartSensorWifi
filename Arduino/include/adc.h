#ifndef ADC_HEADER_
#define ADC_HEADER_

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <serial.h>

/** Initializes the ADC */
void adc_init();
/** Returns the value read on the channel 'channel' of the ADC */
uint8_t adc_get_sample(uint8_t channel);
/** Converts the value of the channel of the ADC into a char[4] */
void adc_to_char(int channel, char* str);
/** Sends the value of the channel 'channel' on the serial port */
void adc_print_conv(int channel);

#endif
