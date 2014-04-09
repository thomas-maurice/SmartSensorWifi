#!/usr/bin/env python
# -*- coding: utf-8 -*-


"""
	configurator.py : Configure serially or over the air smart sensors
	
	           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004
 
	Copyright (C) 2013 Thomas Maurice <tmaurice59@gmail.com>
	 
	Everyone is permitted to copy and distribute verbatim or modified
	copies of this license document, and changing it is allowed as long
	as the name is changed.
	 
		         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
		TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
	 
	 0. You just DO WHAT THE FUCK YOU WANT TO.
	 
"""

__author__ = "Thomas Maurice"
__copyright__ = "Copyright 2013, Thomas Maurice"
__license__ = "WTFPL"
__version__ = "0.1"
__maintainer__ = "Thomas Maurice"
__email__ = "tmaurice59@gmail.com"
__status__ = "Development"

import sys
import socket
import serial
import time
try:
 	import pygtk
  	pygtk.require("2.0")
except:
  	pass
try:
	import gtk
  	import gtk.glade
except:
	sys.exit(1)



class Configurator:
	"""Configurator
	
	This is the main class of the software.
	"""
	
	fileDescriptor = None
	serialDeviceEntry = None
	remoteHostEntry = None
	remoteHostPort = None
	useSerialLink = None
	sensorIDEntry = None
	sensorPasswordEntry = None
	sensorUpdateInterval = None
	dhcpCheckbox = None
	sensorIPEntry = None
	netmaskEntry = None
	gatewayEntry = None
	essidEntry = None
	wirelessKeyEntry = None
	masterKeyEntry = None
	sensorUpdateButton = None
	sensorImportButton = None
	networkTypeCombo = None
	
	def __init__(self):
		"""
		Init function, this will load the glade file and get all the
		interesting widgets as instance variables.
		"""
		# Load the gladefile
		self.gladefile = "configurator.glade"  
		self.windowTree = gtk.glade.XML(self.gladefile) 
	    
		# Get the important widgets
		self.mainWindow = self.windowTree.get_widget("mainWindow")
		
		# The hosts input entries
		self.serialDeviceEntry = self.windowTree.get_widget("serialDeviceEntry")
		self.remoteHostEntry = self.windowTree.get_widget("remoteHostEntry")
		self.remoteHostPort = self.windowTree.get_widget("remoteHostPort")
		self.sensorUpdateInterval = self.windowTree.get_widget("useSerialLink")
		
		# The sensor stuff
		self.sensorIDEntry = self.windowTree.get_widget("sensorIDEntry")
		self.sensorPasswordEntry = self.windowTree.get_widget("sensorPasswordEntry")
		self.sensorPasswordEntry = self.windowTree.get_widget("sensorUpdateInterval")
		
		# The network stuff
		self.dhcpCheckbox = self.windowTree.get_widget("dhcpCheckbox")
		self.sensorIPEntry = self.windowTree.get_widget("sensorIPEntry")
		self.netmaskEntry = self.windowTree.get_widget("netmaskEntry")
		self.gatewayEntry = self.windowTree.get_widget("gatewayEntry")
		self.essidEntry = self.windowTree.get_widget("essidEntry")
		self.wirelessKeyEntry = self.windowTree.get_widget("wirelessKeyEntry")
		self.networkTypeCombo = self.windowTree.get_widget("networkTypeCombo")
		
		# The master key
		self.masterKeyEntry = self.windowTree.get_widget("masterKeyEntry")
		
		# The validate button
		self.sensorUpdateButton = self.windowTree.get_widget("sensorUpdateButton")
		self.sensorImportButton = self.windowTree.get_widget("sensorImportButton")
		
		# Signals
		self.mainWindow.connect("destroy", gtk.main_quit)
		
		# Button signals
		self.sensorUpdateButton.connect("clicked", self.updateSensor)
		self.sensorImportButton.connect("clicked", self.loadSensor)
		
		# checkbox
		self.dhcpCheckbox.connect("toggled", self.dhcpToggled)
	
	def error(self, title, error):
		"""Issues an error window with a close button.
		
		Args:
			title: The title of the error
			error: the pango markuped error body
		
		"""
		d = gtk.MessageDialog(type=gtk.MESSAGE_ERROR, flags=0, buttons=gtk.BUTTONS_CLOSE)
		d.set_title(title)
		d.set_markup(error)
		d.run()
		d.destroy()
	
	def send(self, string):
		if type(self.fileDescriptor)==socket.socket:
			self.fileDescriptor.send(string)
		else:
			self.fileDescriptor.write(string)
	
	def read(self):
		if type(self.fileDescriptor)==socket.socket:
			return self.fileDescriptor.recv(1024)
		else:
			return self.fileDescriptor.read(1024)
	
	def loadSensor(self, data=None):
		"""
		This functions logs you into a sensor (serial or network) and issue
		the AT+IDENT and AT+DUMP config to load the config from  a server to
		the application. So that you don't have to retype everything by hand.
		"""
		if self.masterKeyEntry.get_text() == "":
			self.error("Cannot connect", "The <b>Master key</b> is empty ! You cannot identify onto the sensor. Fill this field and try again :)")
			return
		if self.useSerialLink.get_active() == True:
			print "Connecting to serial sensor"
			try:
				self.fileDescriptor = serial.Serial(self.serialDeviceEntry.get_text())
				self.fileDescriptor.timeout = 0
				self.fileDescriptor.baudrate = 9600
			except SerialException as e:
				print "Cannot open serial port..."
				self.error("Cannot open serial port", "Cannot open serial port... :(")
				return
		else:
			print "Connecting to remote sensor"
			try:
				self.fileDescriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
				self.fileDescriptor.connect((self.remoteHostEntry.get_text(), int(self.remoteHostPort.get_value())))
			except Exception as e:
				print "Cannot connect"
				self.error("Cannot connect", str(e))
				return
		
		if type(self.fileDescriptor)==socket.socket:
			self.fileDescriptor.settimeout(5)
		else:
			self.fileDescriptor.setTimeout(5)
			
		time.sleep(1);
		self.send("\n")
		time.sleep(1)
		self.send("AT+IDENT="+self.masterKeyEntry.get_text()+"\n")
		time.sleep(1)
		self.send("AT+DUMP\n");
		time.sleep(1);
		
		r = self.read()
		print r
		for resp in r.split("\n"):
			resp = resp.strip()
			print resp
			try:
				if "AT+NIP" in resp.split("=")[0]:
					self.sensorIPEntry.set_text(resp.split("=")[1])
				elif "AT+NGW" in resp.split("=")[0]:
					self.gatewayEntry.set_text(resp.split("=")[1])
				elif "AT+NMSK" in resp.split("=")[0]:
					self.netmaskEntry.set_text(resp.split("=")[1])
				elif "AT+ID" in resp.split("=")[0]:
					self.sensorIDEntry.set_text(resp.split("=")[1])
				elif "AT+PW" in resp.split("=")[0]:
					self.sensorPasswordEntry.set_text(resp.split("=")[1])
				elif "AT+MASTER" in resp.split("=")[0]:
					self.masterKeyEntry.set_text(resp.split("=")[1])
				elif "AT+ESSID" in resp.split("=")[0]:
					self.essidEntry.set_text(resp.split("=")[1])
				elif "AT+WKEY" in resp.split("=")[0]:
					self.wirelessKeyEntry.set_text(resp.split("=")[1])
				elif "AT+NETTYPE" in resp.split("=")[0]:
					t =resp.split("=")[1]
					if t=='0':
						self.networkTypeCombo.set_active(0)
					if t=='1':
						self.networkTypeCombo.set_active(1)
					if t=='2':
						self.networkTypeCombo.set_active(2)
					if t=='4':
						self.networkTypeCombo.set_active(3)
					if t=='8':
						self.networkTypeCombo.set_active(4)
				elif "AT+UPINT" in resp.split("=")[0]:
					self.sensorUpdateInterval.set_value(int(resp.split("=")[1]))
				elif "AT+DHCP" in resp.split("=")[0]:
					if resp.split("=")[1] == 1:
						self.dhcpCheckbox.set_active(True)
					else:
						self.dhcpCheckbox.set_active(False)
				
			except:
				pass
				
		self.send("AT+EXIT\n");
		time.sleep(1)
		self.fileDescriptor.close()
		self.fileDescriptor = None
	
	def updateSensor(self, data=None):
		"""
		This builds a new configuration (e.g. AT command list) and
		sends it to the chosen sensor. Either via a serial link or via
		the network. If the configuration is inconsistant (i.e. missing
		fields, the configuration shall not be sent. For now only the
		emptyness of the fields is tested, not the regexp correctness.
		This will come soon. Hopefully
		"""
		if self.masterKeyEntry.get_text() == "":
			self.error("Cannot connect", "The <b>Master key</b> is empty ! You cannot identify onto the sensor. Fill this field and try again :)")
			return
		
		# Building the configuration commands
		
		newConfiguration = ""
		#newConfiguration = "AT+IDENT="+self.masterKeyEntry.get_text()+"\n"
		
		if self.dhcpCheckbox.get_active() == False:
			newConfiguration += "AT+DHCP=0\n"
			if self.sensorIPEntry.get_text()!="" and self.netmaskEntry.get_text()!="" and self.gatewayEntry.get_text()!="":
				newConfiguration += "AT+NIP="+self.sensorIPEntry.get_text()+"\n"
				newConfiguration += "AT+NMSK="+self.netmaskEntry.get_text() + "\n"
				newConfiguration += "AT+NGW="+self.gatewayEntry.get_text() + "\n"
			else:
				self.error("Cannot validate input", "If you don't use DHCP, you need to specify IP, netmask and gateway !")
				return
		else:
			newConfiguration += "AT+DHCP=1\n"
		
		if self.essidEntry.get_text() == "" or self.wirelessKeyEntry.get_text() == "":
			self.error("Cannot validate input", "ESSID or password is empty...")
			return
		else:
			newConfiguration += "AT+ESSID="+self.essidEntry.get_text() + "\n"
			newConfiguration += "AT+WKEY="+self.wirelessKeyEntry.get_text() + "\n"
		
		newConfiguration += "AT+UPINT="+str(int(self.sensorUpdateInterval.get_value()))+"\n"
		
		
		if self.sensorIDEntry.get_text() == "" or self.sensorPasswordEntry.get_text() == "":
			self.error("Cannot validate input", "You need to provide an ID and a password to your sensor")
			return
		else:
			newConfiguration += "AT+ID=" + self.sensorIDEntry.get_text() + "\n"
			newConfiguration += "AT+PW=" + self.sensorPasswordEntry.get_text() + "\n"
		
		if self.networkTypeCombo.get_active_text() == None:
			self.error("Cannot validate input", "You must select a network security !")
			return
		else:
			if self.networkTypeCombo.get_active_text() == "AUTO":
				newConfiguration += "AT+NETTYPE=0\n"
			elif self.networkTypeCombo.get_active_text() == "OPEN":
				newConfiguration += "AT+NETTYPE=1\n"
			elif self.networkTypeCombo.get_active_text() == "WEP":
				newConfiguration += "AT+NETTYPE=2\n"
			elif self.networkTypeCombo.get_active_text() == "WPA-PSK":
				newConfiguration += "AT+NETTYPE=4\n"
			elif self.networkTypeCombo.get_active_text() == "WPA2-PSK":
				newConfiguration += "AT+NETTYPE=8\n"
			else:
				self.error("Cannot validate input", "Invalid network security !")
		
		newConfiguration += "AT+MASTER="+self.masterKeyEntry.get_text()+"\n"
		newConfiguration += "AT+EXIT\n"
		
		if self.useSerialLink.get_active() == True:
			print "Connecting to serial sensor"
			try:
				self.fileDescriptor = serial.Serial(self.serialDeviceEntry.get_text())
				self.fileDescriptor.timeout = 0
				self.fileDescriptor.baudrate = 9600
			except SerialException as e:
				print "Cannot open serial port..."
				self.error("Cannot open serial port", "Cannot open serial port... :(")
				return
		else:
			try:
				self.fileDescriptor = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
				self.fileDescriptor.connect((self.remoteHostEntry.get_text(), int(self.remoteHostPort.get_value())))
			except Exception as e:
				print "Cannot connect"
				self.error("Cannot connect", str(e))
				return
		
		if type(self.fileDescriptor)==socket.socket:
			self.fileDescriptor.settimeout(10)
		else:
			self.fileDescriptor.setTimeout(10)
		
		print newConfiguration
		time.sleep(1)
		#print self.read()
		for c in newConfiguration.split("\n"):
			self.send(c+"\n")
			resp = ""
			print ">", c
			while not "[OK]" in resp and not "[FAIL]" in resp:
				tmp = self.read()
				sys.stdout.write(tmp)
				resp += tmp
				time.sleep(0.2)
			
			if "EXITING" in resp:
				break
		
		self.fileDescriptor.close()
		self.fileDescriptor = None
	
	def dhcpToggled(self, data=None):
		"""This is called whenever the dhcpCheckbox is toggled"""
		if self.dhcpCheckbox.get_active() == True:
			self.sensorIPEntry.set_sensitive(False)
			self.netmaskEntry.set_sensitive(False)
			self.gatewayEntry.set_sensitive(False)
		else:
			self.sensorIPEntry.set_sensitive(True)
			self.netmaskEntry.set_sensitive(True)
			self.gatewayEntry.set_sensitive(True)
			
	def main(self):
		"""Launched the main gtk loop"""
		try:
			gtk.main()
		except KeyboardInterrupt:
			app.mainWindow.destroy()
			print "Exited by user"

if __name__ == "__main__":
	app = Configurator()
	app.main()

