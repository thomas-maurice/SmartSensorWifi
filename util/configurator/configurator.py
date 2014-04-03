#!/usr/bin/env python

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
	"""Configurator"""
	
	fileDescriptor = None
	serialDeviceEntry = None
	remoteHostEntry = None
	remoteHostPort = None
	useSerialLink = None
	sensorIDEntry = None
	sensorPasswordEntry = None
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
		# Load the gladefile
		self.gladefile = "configurator.glade"  
		self.windowTree = gtk.glade.XML(self.gladefile) 
	    
		# Get the important widgets
		self.mainWindow = self.windowTree.get_widget("mainWindow")
		
		# The hosts input entries
		self.serialDeviceEntry = self.windowTree.get_widget("serialDeviceEntry")
		self.remoteHostEntry = self.windowTree.get_widget("remoteHostEntry")
		self.remoteHostPort = self.windowTree.get_widget("remoteHostPort")
		self.useSerialLink = self.windowTree.get_widget("useSerialLink")
		
		# The sensor stuff
		self.sensorIDEntry = self.windowTree.get_widget("sensorIDEntry")
		self.sensorPasswordEntry = self.windowTree.get_widget("sensorPasswordEntry")
		
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
	
	def error(self, title, error):
		d = gtk.MessageDialog(type=gtk.MESSAGE_ERROR, flags=0, buttons=gtk.BUTTONS_CLOSE)
		d.set_title(title)
		d.set_markup(error)
		d.run()
		d.destroy()
	
	def loadSensor(self, data=None):
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
		
		self.fileDescriptor.setTimeout(5)
		time.sleep(1);
		self.fileDescriptor.write("\n")
		time.sleep(1)
		self.fileDescriptor.write("AT+IDENT="+self.masterKeyEntry.get_text()+"\n")
		time.sleep(1)
		self.fileDescriptor.write("AT+DUMP\n");
		time.sleep(1);
		
		r = self.fileDescriptor.read(2048)
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
					
				elif "AT+DHCP" in resp.split("=")[0]:
					if resp.split("=")[1] == 1:
						self.dhcpCheckbox.set_active(True)
					else:
						self.dhcpCheckbox.set_active(False)
				
			except:
				pass
		
		self.fileDescriptor.close()
	
	def updateSensor(self, data=None):
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
			print "Connecting to remote sensor"
		
		print newConfiguration
		time.sleep(2)
		print self.fileDescriptor.read(1024)
		for c in newConfiguration.split("\n"):
			self.fileDescriptor.write(c+"\n")
			resp = ""
			print ">", c
			while not "[OK]" in resp and not "[FAIL]" in resp:
				tmp = self.fileDescriptor.read(1024)
				sys.stdout.write(tmp)
				resp += tmp
				time.sleep(0.2)
			
			if "EXITING" in resp:
				break
		
		self.fileDescriptor.close()
			
	def main(self):
		try:
			gtk.main()
		except KeyboardInterrupt:
			app.mainWindow.destroy()
			print "Exited by user"

if __name__ == "__main__":
	app = Configurator()
	app.main()
	#try:
	#	gtk.main()
	#except KeyboardInterrupt:
	#	app.mainWindow.destroy()
	#	print "Exited by user"

