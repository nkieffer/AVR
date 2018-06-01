hex:
	avr-g++ -Os  -DF_CPU=1000000 -mmcu=attiny85 -c main.c
	avr-g++ -DF_CPU=1000000 -mmcu=attiny85 -o main.elf main.o
	avr-objcopy -O ihex main.elf main.hex

install: hex
	avrdude -c arduino -p attiny85 -P /dev/cu.wchusbserialfd1410 -U flash:w:main.hex -b 19200

