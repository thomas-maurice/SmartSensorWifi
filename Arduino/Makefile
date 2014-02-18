# AVR standard Makefile.
# Author: Thomas Maurice
# Options :
#	By default, the ROM will be output, there are several other options :
#		- all : the rom + the eeprom file
#		- nuke : Deletes all the .o, .hex and .elf
#		- clean : Deletes all the binaries
# 	- rebuild : nuke + all
#		- erase : erase the chip	
#		- flash : flashes the rom + the eeprom
#		- check : check if all the hex are size-compliant for the mcr
#		- fuse : flashes the correct fuses for the project
#		- dist : builds a nice .tgz file with the sources and the .hex and .eep

# Compiler
COMPILER=avr-gcc
OBJCOPY=avr-objcopy
# Source and include directory
SRCDIR=src
INCLUDEDIR=include
# Appareil
DEVICE=atmega328p
FREQU=16000000L
# Fuses
LFUSE=0x94
HFUSE=0xd9
# AVRDUDE configuration
TERM=/dev/ttyACM0
# Programmer type
#ISP_DEVICE_NAME=usbasp
ISP_DEVICE_NAME=stk500v1 -b 115200 -F -v -P $(TERM)
#ISP_DEVICE_NAME=stk500v1 -v -v -b 57600 -F -v -P $(TERM)
# Microcontroller type
MC_TYPE=atmega328p
# Compiler flags
OPTFLAGS=-Os -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions
FLAGS=$(OPTFLAGS) -std=gnu99 -I$(INCLUDEDIR) -Wno-write-strings -ffunction-sections -mmcu=$(DEVICE) -DF_CPU=$(FREQU)
# Liner flags
LDFLAGS=-mmcu=$(DEVICE) #-Wl,-gc-sections
#  File extension (ex "c" for C code)
SRCEXT=c
# Binary names
BIN=$(shell basename `pwd`).elf
ROM=$(shell basename `pwd`).hex
EEPROM=$(shell basename `pwd`).eep

# Source files
SRC=$(wildcard $(SRCDIR)/*.$(SRCEXT) $(SRCDIR)/*.S)
# Object files
W_ASM=$(SRC:.$(SRCEXT)=.o)
OBJ=$(W_ASM:.S=.o)
# Archive dir
DISTDIR=$(shell basename `pwd`)-src

# Special targets
all: $(ROM) $(EEPROM) size
rebuild: nuke all

size: $(BIN)
	avr-size --format=avr --mcu=$(DEVICE) $(BIN) | egrep "(Full|^Device)"

erase:
	avrdude -p $(MC_TYPE) -c $(ISP_DEVICE_NAME) -e
	
# The ROM
$(ROM): $(BIN)
	$(OBJCOPY) -j .text -j .data -O ihex $(BIN) $(ROM)

# The EEPROM
$(EEPROM): $(BIN)
	$(OBJCOPY) -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex $(BIN) $(EEPROM)

# The binary file
$(BIN): $(OBJ)
	$(COMPILER) -o $(BIN) $(OBJ) $(LDFLAGS)

# .o files
%.o: %.$(SRCEXT)
	$(COMPILER) $(FLAGS) -c $< -o $@

%.o: %.S
	$(COMPILER) $(FLAGS) -x assembler-with-cpp -c $< -o $@

# Fuses
fuse:
	avrdude -p $(MC_TYPE) -c $(ISP_DEVICE_NAME) -U lfuse:w:$(LFUSE):m
	avrdude -p $(MC_TYPE) -c $(ISP_DEVICE_NAME) -U hfuse:w:$(HFUSE):m

# Flashes the ROM onto the µC
# Requires to be root
flash: $(ROM) $(EEPROM)
	stty -F $(TERM) hupcl
	avrdude -p $(MC_TYPE) -c $(ISP_DEVICE_NAME) -U flash:w:$(ROM):i
	avrdude -p $(MC_TYPE) -c $(ISP_DEVICE_NAME) -U eeprom:w:$(EEPROM):i

# Clean target
clean:
	rm -f $(OBJ)
	rm -f $(BIN)

# Kaboom !
nuke: clean
	rm -f $(ROM)
	rm -f $(EEPROM)
	rm -f $(DISTDIR).tgz

# Distribution traget
dist: all clean
	if ! [ -d $(DISTDIR) ]; then mkdir $(DISTDIR); fi;
	if ! [ -d $(DISTDIR)/$(SRCDIR) ]; then mkdir $(DISTDIR)/$(SRCDIR); fi;
	if ! [ -d $(DISTDIR)/$(INCLUDEDIR) ]; then mkdir $(DISTDIR)/$(INCLUDEDIR); fi;
	if [ -e $(ROM) ]; then cp $(ROM) $(DISTDIR); fi;
	if [ -e $(EEPROM) ]; then cp $(EEPROM) $(DISTDIR); fi;
	if [ -e getfuses.sh ]; then cp getfuses.sh $(DISTDIR); fi;
	if [ -e check.sh ]; then cp check.sh $(DISTDIR); fi;
	if [ -e "INSTALL" ]; then cp INSTALL $(DISTDIR); fi;
	if [ -e "LICENSE" ]; then cp LICENSE $(DISTDIR); fi;
	if [ -e "AUTHORS" ]; then cp AUTHORS $(DISTDIR); fi;
	if [ -e "COPYING" ]; then cp COPYING $(DISTDIR); fi;
	cp -r $(SRCDIR) $(DISTDIR)
	cp -r $(INCLUDEDIR) $(DISTDIR)
	cp Makefile $(DISTDIR)
	tar zcvf $(DISTDIR).tgz $(DISTDIR)
	rm -r $(DISTDIR)

.PHONY: nuke clean flash dist nuke fuse check rebuild
