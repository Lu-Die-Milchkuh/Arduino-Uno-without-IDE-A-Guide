CC 			= avr-gcc
DEV 		= atmega328p
PROGRAMMER 	= arduino
PORT 		= /dev/ttyACM0
BAUD 		= 115200
COMPILE		= $(CC) -Wall -Os -mmcu=$(DEV) 
FILENAME 	= blink

default: compile upload 

compile:
	
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEV) $(FILENAME).elf

upload:
	avrdude -v -p $(DEV) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i
