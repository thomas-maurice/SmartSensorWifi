# Configurator
*one software to conf them all*

## Introduction
If you succeeded to build a sensor and to upload a firmware onto it (GG)
you are probably wondering "How the hell am I supposed to confiigure it
in order to make it work with my network and with my server" aka "WTF?".

Well **configurator.py** is the answer ! This software is designed to allow
you to configure a sensor device either from your computer through the network
or through a serial link to perform the initial configuration.

## How do I launch it ?
That's rather easy. You just fave to go into the util/configurator folder
then run `python configurator.py`. Note that you have some dependencies to
satisfy in order to run the software, namely :

 * python (you don't say)
 * python-serial
 * python-gtk, python-gtk2 or pygtk depending on how the package is called in your distro

## How do I use it ?
Well, the interface is quite simple actually. And the field are quite self
explanatories. All you need to do is to fill in all the forms and hit the
"Connect and upload" button. If some important fields are not properly filled
then an error shall be raised and nothing will be uploaded. You will not break your config :)

If you just want to edit it, you can alternatively load the config from a sensor
to your interface. Then identically just hit the "Connect and download" button.

## Let's do that !
Yep, but before you get frustrated because "stupid software won't work" you
have to know that an initial serial configuration requires a slight physical
interraction with the device. That is to say you have to do two things :
firstly you have to change the switch of the wifi shield from the "Run" to
the "Prog" mode. Then while pressing the "Download" or "Upload" button you
have to press the pushbutton located on the right part of the shield. This will
allow the device to be serially configured.

To do this wirelessly you don't need such manipulations. Just fill in the address
and here you go !

## Master key
Note that you don't need to provide the master key if you are reprograming
the software via the serial link.
