all:	hex install

hex:
	@echo "Starting compilation..."
	avr-g++ -Os -Wextra -DF_CPU=9600000 -mmcu=attiny13 -c main.c
	avr-g++ -DF_CPU=9600000 -mmcu=attiny13 -o main.elf main.o
	avr-objcopy -O ihex main.elf main.hex

install:
	@echo "Starting installation..."
	avrdude -c arduino -p attiny13 -P /dev/cu.usb* -U flash:w:main.hex -b 19200

