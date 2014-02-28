# Smart Sensor WiFi - microcontroller Part
## General information

 * Developpement status : *work in progress*
 * Project version   : 0.1 alpha
 * Developper : Thomas Maurice <Thomas.Maurice@polytech-lille.net>

# Introduction
 
This project is a student project managed by Polytech Lille Engineering
School. It is led by two students, *Thomas Maurice* and *Benoit Maliar*. Both
students in 4th year.

The aim of the project is to create a distributed WiFi sensor network
that is able to regularly communicate various data to a central DB and
autoreconfigure itself in order to be energy efficient.

Note that the project is open source and you can modify it. Especially
the drivers for the RTC and the WiFi chip, you are more than welcome to
study and improve them.

# Hardware

The project uses the following hardware :

* An atmega328p (An Arduino Uno board for the developpement).
* A DS1302 real time clock for time-keeping.
* A photoresistor and temperature sensor.
* A WizFi210 WiFi chip.

# Compiling

To compile the project you just need AVR-gcc installed. Just go in the
`Arduino` directory and run `make`. Everything will compile well. If
not, just undo your changes to my code !

It will create a nice .hex for upload. If your target is an Arduino board
then just type `make flash` to upload it using the built-in bootloader.
If it is just a bare-metal atmega328p then wire it up to your USBASP
device and run avrdude with the good options.

Have fun :)
