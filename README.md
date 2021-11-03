# Arduino-Uno-without-IDE-A-Guide
***Note: this guide only covers Linux!***
## Introduction
So you want to program your Arduino Uno but you think you dont learn anything doing it with the Arduino IDE? Dont look further,you have came to the right place!
Before we can begin we need some tools (so called toolchain). This basically contains avr-gcc(a compiler),avr-libc(avr-library) and avr-dude(a program to upload our code to the Arduino).

## Prerequiste
**1) install AVR-GCC:**
  - Ubuntu/Debian
    - ```
      sudo apt install gcc-avr
      ```
  - Arch
    - ```
      sudo pacman -S avr-gcc
      ```
**2) install AVR-DUDE:**
  - Ubuntu/Debian
    - ```
      sudo apt install avrdude
      ```
  - Arch
    - ```
      sudo pacman -S avrdude
      ```
**3) install necessary Library:**     
  - Ubuntu/Debian
    - ```
      sudo apt install avr-libc
      ```
  - Arch
    - ```
      sudo pacman -S avr-libc
      ```
