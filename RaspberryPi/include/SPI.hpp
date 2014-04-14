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
 * \file SPI.hpp
 * \author Thomas Maurice
 * 
 * \brief SPI port base class definition
 * \version 0.1
 */

/**
 * \class SPI
 * \brief Base class to describe the SPI port
 * 
 * This class describes a basic SPI port. All the SPI "drivers" you want
 * to implement must interit from this class. It provides a basic function
 * base to create, open, close and manipulate data through the SPI port.
 * 
 * It enables you to realize full duplex SPI communications between your
 * program and any SPI device.
 *
 * See the mainpage for an exemple of usage
 */ 

/**
 * \mainpage
 *
 * This project aims to make easy the interafcing of SPI devices with your RaspberryPi
 * or any SPI-enabled device. It provides a base class (called simply SPI) that
 * provides basic functionalities and can be inherited from to manipulate some
 * more complex devices.
 * 
 *  So all you need to do is to redefine a new class like it follows :
 * 
 * \code {.cpp}
 * 
 * class SPIDevice : public SPI {
 *	public:
 *		SPIDevice(std::string spifile, int speed, int mode = SPI_MODE_0, int bits_p_word = 8) :
 * 			SPI(spifile, speed, mode, bits_p_word) {
 * 			// Here goes addiditonal initialization operation
 * 		}
 * 		
 * 		// Reads a value from the device (EEPROM for exemple), here the address
 * 		// is 24 bits long and the result is a 8 bits value. To read it we have to send
 * 		// The following sequence to the device : 
 *     	// READ_OPCODE, ADDR1, ADDR2, ADDR3, EXTRA
 * 		// The EXTRA byte is used to retrieve data from the device.
 * 		int readValue(int address) {
 * 			unsigned char command[5];
 * 			command[0] = READ_OPCODE;
 * 			command[1] = addr & 0xFF;
 * 			command[2] = (addr>>8) & 0xFF;
 * 			command[3] = (addr>>16) & 0xFF;
 * 			command[4] = 0; // This one is used to retrieve the value we want to read
 * 			this->transfer(command, 5);
 * 			// The result is now in command[4], all the other bytes are useless
 * 			return command[4];
 * 			// Pretty neat isn't it ? ;)
 * 		}
 * 
 * 	protected:
 * 		// Here go your protected attributes
 * 
 *	private:
 * 		// Here go your local attributes
 * };
 * 
 * \endcode
 * 
 * To use this code in your main.cpp, all you need to do is :
 * \code {.cpp}
 * #include <SPIDevice.hpp>
 * #include <iostream>
 * 
 * using namespace std;
 * 
 * int main(int argc, char ** argv) {
 * 		// Create a device at 1MHz, SPI mode 0 on /dev/spidev0.0
 * 		SPIDevice dev = SPIDevice("/dev/spidev0.0", 1000000, SPI_MODE_0);
 * 		cout << "Value : " << dev.readValue(0x000) << endl; // Read the base value of the EEPROM
 * 		return EXIT_SUCCESS;
 * }
 * 
 * \endcode
 * 
 * This is way more easy than doing it the [spidev way](http://lxr.free-electrons.com/source/drivers/spi/spidev.c), isn't it ?
 */
#ifndef SPI_PORT_H
#define SPI_PORT_H

#include <iostream>
#include <linux/spi/spidev.h>

class SPI {
	public:
		/* Constructors and destructors */
		SPI(std::string spifile, int speed, int mode = SPI_MODE_0, int bits_p_word = 8); //!< SPI port constructor
		~SPI();
		
		/* Nested data structures */
		enum Status {
			Opened,
			Closed,
			Error,
			Success
		}; //!< Enum resuming the various states of the SPI port

		/* I/O Operations */
		SPI::Status close_port(); //!< Closes the port
		SPI::Status open_port(); //!< Opens the port
		SPI::Status transfer(unsigned char* command, int cmd_len); //!< Transfers a buffer

		/* Getters */
		SPI::Status get_status() const; //!< Returns the status of the port
		int get_speed() const; //!< Returns the speed of the bus
		int get_mode() const; //!< Returns the mode of the bus
		int get_bits_per_word() const; //!< Returns the number of BPW

	protected:
		std::string spi_dev_file; //!< Spi file name
		int spi_fd; //!< Spi file descriptor
		int spi_mode; //!< Spi mode
		int spi_speed; //!< Spi speed
		int spi_bits_per_word; //!< Spi number of bits per word
		SPI::Status status; //!< The current status of the bus
};

#endif

/* EOF */
