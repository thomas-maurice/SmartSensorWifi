#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <SPI.hpp>
#include <SPI_MCP3208.hpp>

using namespace std;

int main(int argc, char ** argv) {
	SPI_MCP3208 port = SPI_MCP3208("/dev/spidev0.0", 500000, SPI_MODE_0, 8);
	port.open_port();
	uint16_t val = port.readValue(true, 0);
	std::cout <<  "Valeur dec " << val << std::endl;
	port.close_port();
	return EXIT_SUCCESS;
}
