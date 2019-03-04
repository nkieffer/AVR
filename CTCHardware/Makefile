all: hex install

hex:
	avr-g++ -Os  -DF_CPU=1000000 -mmcu=attiny85 -c main.c
	avr-g++ -DF_CPU=1000000 -mmcu=attiny85 -o main.elf main.o
	avr-objcopy -O ihex main.elf main.hex

install:
	avrdude -c arduino -p attiny85 -P /dev/cu.usbmodemFD1411 -U flash:w:main.hex -b 19200

clean:
	rm -i *.elf *.hex *.o *~
