# Communicate with the SmartSensors via AT-commands

## Introduction
If you are familiar with the use of microcontroller devices such as
XBee chips or so you migh know what the AT commands ar for : they
enables you to configure your device via a textual mode. You are very
lucky since the SmartSensors are shipped with a set of a dozen AT commands
which enable you to configure it quite easily.

The main advantage of these AT commands is that they are accessible
both in serial mode *as well as* in WiFi mode. That is to say that
you can reconfigure your sensors remotely via the wifi, provided the sensor
has already access to a network. Cool isn't it ?

To do so, the `util/` folder contains the **configurator.py** software
wich can connect and update/download a sensor configuration. Just run it
the fields/buttons are quite self explanatory.

## Identification
To identify on the sensor, you have to know something called the **master key**
of the sensor. This is a code that you must enter before trying to do anything
on the sensor. The command for that is `AT+IDENT=masterkey`.

## The commands

The generic syntax for an AT command is the following : `AT+COMMAND=ARG`. If you
are coding something about it, don't forget to add an `\n` or an `\r` after
the command.

### Sensor configuration
These commands are used to configure the sensor itself and it's identification
onto your database server.

 * `AT+ID` : Changes the ID of the sensor to access the website
 * `AT+PW` : Changes it's password
 * `AT+IPDB` : Changes the IP of the data server
 * `AT+HOSTDB` : Changes the hostname of the data server

### Network configuration
 
 * `AT+DHCP` : 1 if DHCP is used, 0 if not. If DHCP is used you don't need further config.
 * `AT+NIP` : IP address of the sensor
 * `AT+NGW` : Gateway IP
 * `AT+NMSK` : Netmask

### Wireless configuration

 * `AT+ESSID` : Obviously sets the ESSID of the network. Does not matter if visible or not
 * `AT+WKEY` : Sets the passphrase for the sensor
 * `AT+NETTYPE` : Sets the type of network according to the following values :
    * 0 : Auto
    * 1 : Open authentication
    * 2 : WEP authentication
    * 4 : WPA PSK
    * 8 : WPA2 PSK

### Security

 * `AT+MASTER` : Changes the Master key.
 * `AT+IDENT` : Identify on the sensor. The parameter is the master key.
 
### End of sequence

 * `AT+EXIT` : This command shall be issued at the end of every command sequence end.
