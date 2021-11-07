# Arduino-Uno-without-IDE-A-Guide
***Note: this guide only covers Linux!***

# Table of contents
* [Introduction](#Introduction)
* [Prerequiste](#Prerequiste)
* [Configuration](#Configuration)
* [Hello Atmega328p!](https://github.com/Lu-Die-Milchkuh/Arduino-Uno-without-IDE-A-Guide#hello-atmega328p)
* [Lets code!](https://github.com/Lu-Die-Milchkuh/Arduino-Uno-without-IDE-A-Guide#lets-code)

# Introduction
So you want to program your Arduino Uno but you think you will not learn anything doing it with the [Arduino IDE](https://www.arduino.cc/en/Main/Software_)? Dont look further, you came to the **right** place!
Before we can begin we need some tools (so called toolchain). This basically contains avr-gcc(a compiler), avr-libc(avr-library) and avr-dude(a program to upload our code to the Arduino).

# Prerequiste

**1) Install AVR-GCC:**
  - Ubuntu/Debian
    ```
    sudo apt install gcc-avr
    ```
  - Arch
    ```
    sudo pacman -S avr-gcc
    ```
**2) Install AVR-DUDE:**
  - Ubuntu/Debian
    ```
    sudo apt install avrdude
    ```
  - Arch
    ```
    sudo pacman -S avrdude
    ```
**3) Install necessary Library:**     
  - Ubuntu/Debian
    ```
    sudo apt install avr-libc
    ```
  - Arch
    ```
    sudo pacman -S avr-libc
    ```

# Configuration

To  be able to flash our code later to our Arduino, we need to know which port belongs to it. Furthermore we need to enable read/write permission on that port. 

***Note: Plug in your Arduino to your PC via USB before you proceed!***
- **Find out what port to use:**
  ```
  ls /dev/tty*  OR sudo dmesg (less clear!)
  ```
  Your port will look like(or similar) this: 
  ```
  /dev/ttyACM0
  ```

- **Find the owner of this port:**
  ```
  ls -l /dev/ttyACM*
  ```     
  You should get something like this :
  
  ```
  crw-rw---- 1 root uucp 166, 0  3. Nov 16:40 /dev/ttyACM0
  ```
   The owner is right behind root, in my case its "uucp" !
     
- **Enable Read/Write Permission:**
  ```
  sudo usermod -a -G <OWNER> <YOURUSERNAME>
  ```
    ***Note: Log out and in again or just reboot your PC!***
    
 - Thats all you have to do for your OS Configuration.

# Hello Atmega328p!

- Before we can start coding, we need to take a look at the [datasheet](https://github.com/Lu-Die-Milchkuh/Arduino-Uno-without-IDE-A-Guide/blob/main/Documentation/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf) for the Atmega328p, which is the CPU used in the Arduino Uno:

```
- 8-Bit Microcontroller
- 132 instructions
- 32 KB Flash memory
- 1 KB EEPROM
- 2 KB SRAM
- 32x8 Registers  // This is what we will use the most
```

- Every PIN on the Arduino is controlled by 3 Bits from 3 different Registers(DDxn,PORTxn and PINxn). But we really only need DDxn and PORTxn

```c
- DDxn -> set PIN to Output/Input-Mode
- PORTxn -> set PIN high/low
```

***Note: to see which Port-Register belongs to which PIN on the Arduino, have a look at this [diagram](https://github.com/Lu-Die-Milchkuh/Arduino-Uno-without-IDE-A-Guide/blob/main/Documentation/pinPort.png)***

# Lets code!  
To test that everything is working as intended, lets create the "Hello World" program of all microcontrollers => blinking a LED!


- First of all , lets create a Makefile that makes things much easier for us:



```make
CC 		= avr-gcc                           # Setting our Compiler to AVR-GCC
DEV 		= atmega328p                        # Defining our Device
PROGRAMMER 	= arduino                           # What Programmer we use(Arduino Board)
PORT 		= /dev/ttyACM0                      # Set this to YOUR port!
BAUD 		= 115200                            # max baudrate, just leave it like this
COMPILE		= $(CC) -Wall -Os -mmcu=$(DEV) 
FILENAME 	= blink                             # set this to the name you gave your .c-file

default: compile upload                     # If we call "make" , this 2 steps will be executed     

compile:                                    # Compiling our code to Intel-Hex
	
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEV) $(FILENAME).elf

upload:                                     # Uploading our Code to the Arduino

	avrdude -v -p $(DEV) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i
```
***Note: We will later just call this Makefile(via *make* in a terminal) so we dont have to re-type every single command manually.***



- So now lets create the actually source code: 

```c
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__  // Defining which CPU we are using
#endif

#define F_CPU 16000000UL // ATmega328p Frequency, needed to get correct delays!

#include <avr/io.h> // Standard Input/Output library, contains predefined variables etc
#include <util/delay.h> // library containing delay-function



int main(void) {

    DDRD = 0b01000000; //  Setting Bit to 1 sets the Pin to Output
    
    /*
      Toggling PIN 6 on/off
    */
    for(;;) 
    {
        
        PORTD ^= (1<<6);  // Toggling the sixth bit on and of with a bitwise xor!
        _delay_ms(1000);  // Sleeping for 1 sec  

        
    }
    
    return 0;
}
```

***Note: I called my file *blink.c*, if you want to chose another name, remember to change the FILENAME-argument in the Makefile!***  

- Compile and upload your code now by calling *make* in a terminal. Make sure your Arduino is plugged into your PC!

All of my code can be found [here](https://github.com/Lu-Die-Milchkuh/Arduino-Uno-without-IDE-A-Guide/tree/main/Code)