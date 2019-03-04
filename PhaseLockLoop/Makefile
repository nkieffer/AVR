install: main.hex
	avrdude -c arduino -p attiny85 -P /dev/cu.usbmodem* -U flash:w:main.hex -b 19200

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex
	@echo "happy elf"

main.o: main.c
	avr-g++ -Os  -DF_CPU=1000000 -mmcu=attiny85 -c main.c

main.elf: main.o
	avr-g++ -DF_CPU=1000000 -mmcu=attiny85 -o main.elf main.o

clean: rm -i *.o *.elf *.hex *~

