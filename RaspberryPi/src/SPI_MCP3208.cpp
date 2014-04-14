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
 * \file SPI_MCP3208.hpp
 * \author Thomas Maurice
 * 
 * \brief SPI driver header for the MCP3208 ADC
 * \version 0.1
 */
 
#include <SPI_MCP3208.hpp>
#include <bitset>

/**
 * Default contructor, see the SPI class documentation for more information
 * 
 * \see SPI
 */
SPI_MCP3208::SPI_MCP3208(std::string spifile, int speed, int mode, int bits_p_word) :
	SPI(spifile, speed, mode, bits_p_word) {
	
}

/**
 * Returns a value on the given channel
 * 
 * \param [in] single_ended Do we proceed to a single ended or differential conversion ?
 * \param [in] channel The channel to convert. In differential mode see the datasheet for the values
 * 
 * \returns The value returned by the ADC (between 0 and 2^12)
 */
uint16_t SPI_MCP3208::readValue(bool single_ended, unsigned char channel) {
	unsigned char command_bytes[6] = {0};
	memset(command_byte, 6, 0);
	command_bytes[0] |= 0x4; // The start bit
	if(single_ended)
		command_bytes[0] |= 0x02; // Single or differential mode
	
	command_bytes[0] |= (channel>>1);
	
	command_bytes[1] |= ((channel&0x01)<<7);
	
	//for(int i = 0; i < 4; i++)
	//	std::cout << std::hex << " 0x" << (int)command_bytes[i];
	
	//std::cout << std::endl;
	
	transfer(command_bytes, 4);
	
	//for(int i = 0; i < 4; i++)
	//	std::cout << " " << (std::bitset<8>((int)command_bytes[i]));
	
	//std::cout << std::endl;
	
	std::cout << std::hex << "0x" << (int)command_bytes[2] << (int)command_bytes[3]<<std::endl;
	
	uint16_t result = ((command_bytes[2]&0x0F)<<8)+command_bytes[3];
	std::cout << std::hex << "0x" << result << std::endl;
	return result;
}
