# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected.
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.
$(info Set the PORT)
DEVICE     = attiny85
CLOCK      = 8000000
PORT	   = /dev/cu.usbm*
PROGRAMMER =  -p $(DEVICE) -c arduino -P $(PORT) -b 19200
OBJECTS    = main.o I2C.o
FUSES      = -U lfuse:w:0x64:m -U hfuse:w:0xdd:m -U efuse:w:0xff:m

include ../.config/common.make
######################################################################
######################################################################

