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
 * \file SPI_MCP3208.cpp
 * \author Thomas Maurice
 * 
 * \brief SPI driver for the MCP3208 ADC
 * \version 0.1
 */
#include <SPI.hpp>
#include <stdint.h>

/**
 * \class SPI_MCP3208
 * \brief A class to read from Microchip's MCP3208 ADCs
 */

class SPI_MCP3208 : public SPI {
	public:
		/** Default consctructor */
		SPI_MCP3208(std::string spifile, int speed, int mode = SPI_MODE_0, int bits_p_word = 8);
		/** Reads a value from the ADC */
		uint16_t readValue(bool single_ended, unsigned char channel);
	private:
};
