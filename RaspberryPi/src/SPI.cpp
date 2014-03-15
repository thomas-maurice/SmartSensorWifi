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
 * \file SPI.cpp
 * \author Thomas Maurice
 * 
 * \brief SPI base class implementation
 * \version 0.1
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/spi/spidev.h>
#include <errno.h>
#include <unistd.h>
#include <memory.h>

#include <SPI.hpp>

/**
 * Constructor to create a new SPI port. spifile is like "/dev/spidev0.0".
 * Speed should not exceed 12MHz. Mode can take the following values, eventually
 * combined by a | :
 *  * SPI_MODE_0 (not to combine with SPI_MODE_1,2,3 ofc)
 *  * SPI_MODE_1
 *  * SPI_MODE_2
 *  * SPI_MODE_3
 *  * SPI_CS_HIGH to enable the device with a high CS
 *  * SPI_LSB_FIRST to transmit the LSB first
 *  * SPI_3WIRE
 *  * SPI_LOOP
 *  * SPI_NO_CS
 *  * SPI_READY
 * 
 * Don't worry ! Usually SPI_MODE_0 is good enough :) And finally you can specifiy the number
 * of bits per word you like, usually it will be 8.
 * 
 * \param [in] spifile The file name for the SPI port
 * \param [in] speed The speed in Hertz of the spi bus
 * \param [in] mode The mode of the bus (TL;DR use SPI_MODE_0)
 * \param [in] bits_p_word Number of bits per word
 */
SPI::SPI(std::string spifile, int speed, int mode, int bits_p_word) {
	spi_dev_file = spifile;
	spi_mode = mode;
	spi_speed = speed;
	spi_bits_per_word = bits_p_word;
}

/**
 * Opens the SPI port and configure it with the parameters specified in
 * the constructor. On error it will return SPI::Error and print the
 * corresponding error messages via perror.
 * 
 * \return SPI::Success on success and SPI::Error otherwise. It will
 * also print an error message (via perror) to specify what went wrong.
 */
SPI::Status SPI::open_port() {
	spi_fd = open(spi_dev_file.c_str(), O_RDWR);
	status = SPI::Opened;
	
	if(spi_fd < 0) {
		perror("spi open");
		status = SPI::Error;
		return status;
	}

	if(ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode)<0) {
		perror("can't set wr mode");
		status = SPI::Error;
		return status;
	}
	
	if(ioctl(spi_fd, SPI_IOC_RD_MODE, &spi_mode)<0) {
		perror("can't set rd mode");
		status = SPI::Error;
		return status;
	}

	if(ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits_per_word)<0) {
		perror("can't set wr bpw");
		status = SPI::Error;
		return status;
	}

	if(ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bits_per_word)<0) {
		perror("can't set rd bpw");
		status = SPI::Error;
		return status;
	}

	if(ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed)<0) {
		perror("can't set wr speed");
		status = SPI::Error;
		return status;
	}

	if(ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed)<0) {
		perror("can't set rd speed");
		status = SPI::Error;
		return status;
	}
	
	return status;
}

/**
 * Gets the speed of the bus
 * 
 * \return the speed of the bus
 */
int SPI::get_speed() const {
	return spi_speed;
}

/**
 * Gets the number of bits per word
 * 
 * \return the number of bits per word
 */
int SPI::get_bits_per_word() const {
	return spi_bits_per_word;
}

/**
 * Returns the mode of the  bus
 * 
 * \return the mode of the bus
 */
int SPI::get_mode() const {
	return spi_mode;
}

/**
 * Returns the status of the port. It can either be SPI::Opened, SPI::Closed
 * or SPI::Error.
 * 
 * \return The status of the port
 */
SPI::Status SPI::get_status() const  {
	return status;
}

/**
 * Transfers a buffer to the SPI device. The return values are stored in
 * the transmission buffer. It means that every data in command will be
 * overwritten after the transfert. You have to process them to extract
 * all the relevant info you need.
 * 
 * \param [inout] command The Tx/Rx buffer (you must reserve space into
 * it in case the SPI device returns some response sequence, for exemple
 * if you want to read an eeprom).
 * \param [in] cmd_len The length of the command to transmit (you must
 * have some zero padded extra space if you want your command to return a result)
 * 
 * \return SPI::Success on succes and SPI::Error on error
 */
SPI::Status SPI::transfer(unsigned char *command, int cmd_len) {
	struct spi_ioc_transfer transfer_buffer;
	transfer_buffer.tx_buf = (__u64)command;
	transfer_buffer.rx_buf = (__u64)command;
	transfer_buffer.len =  (__u32)cmd_len;
	transfer_buffer.speed_hz = (__u32)spi_speed;
	transfer_buffer.delay_usecs = (__u16)1;
	transfer_buffer.bits_per_word = (__u8)spi_bits_per_word;
	transfer_buffer.cs_change = (__u8)0;
	transfer_buffer.pad = (__u32)0;

	if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &transfer_buffer) < 0) {
		perror("SPI_IOC_MESSAGE");
		status = SPI::Error;
		return SPI::Error;
	}
	
	return SPI::Success;
}

/**
 * Closes the SPI port
 * 
 * \return SPI::Success on success and SPI::Error otherwise
 */
SPI::Status SPI::close_port() {
	if(close(spi_fd)<0) {
		perror("close");
		status = SPI::Error;
		return SPI::Error;
	} else {
		status = SPI::Closed;
		return SPI::Success;
	}
}

/**
 * Destructor. Closes the port if it is not closed.
 */
SPI::~SPI() {
	if(status == SPI::Closed || SPI::Error)
		return;
	else
		close_port();
}
