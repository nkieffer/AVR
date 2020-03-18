

######################################################################
######################################################################

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
$(info $(AVRDUDE))
# symbolic targets:
all:	main.hex

%.o : %.c
	@echo $@
	 $(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash #fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS) *~

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c

.PHONY: readfuse
readfuse:
	@$(AVRDUDE) -qqq -U efuse:r:.efuse:b -U hfuse:r:.hfuse:b -U lfuse:r:.lfuse:b 
	@echo -n EFUSE: 
	@cat .efuse
	@echo "0 => SELFPRGEN"
	@echo -n HFUSE: 
	@cat .hfuse
	@echo "0-2 => BODLEVEL"
	@echo "3 => EESAVE"
	@echo "4 => WDTON"
	@echo "5 => SPEIN"
	@echo "6 => DWEN"
	@echo "7 => RSTDISBL"
	@echo -n LFUSE: 
	@cat .lfuse
	@echo "0-3 => CKSEL"
	@echo "4-5 => SUT"
	@echo "6 => CKOUT"
	@echo "7 => CKDIV8"
	@rm .efuse .hfuse .lfuse
