hex:
	avr-g++ -Os  -DF_CPU=1000000 -mmcu=attiny85 -c main.c
	avr-g++ -DF_CPU=1000000 -mmcu=attiny85 -o main.elf main.o
	avr-objcopy -O ihex main.elf main.hex

install:
	avrdude -c arduino -p attiny85 -P /dev/cu.usb* -U flash:w:main.hex -b 19200

