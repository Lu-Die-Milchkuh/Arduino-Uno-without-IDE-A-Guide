# Arduino-Uno-without-IDE-A-Guide
***Note: this guide only covers Linux!***
## Introduction
So you want to program your Arduino Uno but you think you dont learn anything doing it with the [Arduino IDE](https://www.arduino.cc/en/Main/Software_)? Dont look further,you have came to the **right** place!
Before we can begin we need some tools (so called toolchain). This basically contains avr-gcc(a compiler),avr-libc(avr-library) and avr-dude(a program to upload our code to the Arduino).

## Prerequiste
**1) Install AVR-GCC:**
  - Ubuntu/Debian
    - ```
      sudo apt install gcc-avr
      ```
  - Arch
    - ```
      sudo pacman -S avr-gcc
      ```
**2) Install AVR-DUDE:**
  - Ubuntu/Debian
    - ```
      sudo apt install avrdude
      ```
  - Arch
    - ```
      sudo pacman -S avrdude
      ```
**3) Install necessary Library:**     
  - Ubuntu/Debian
    - ```
      sudo apt install avr-libc
      ```
  - Arch
    - ```
      sudo pacman -S avr-libc
      ```
## Configure your OS

To  be able to flash our code later to our Arduino,we need to know which port belongs to it. Furthermore we need to enable read/write permission on that port. 

***Note: Plug in your Arduino to your PC via USB before you proceed!***
- **Find out what port to use:**
  - ```
    ls /dev/tty*  OR sudo dmesg (less clear!)
    ```
  Your port will look like(or similar) this: 
   - ```
     /dev/ttyACM0
     ```
- **Find the owner of this port:**
   - ```
     ls -l /dev/ttyACM*
     ```     
     You should get something like this :
     - ```
       crw-rw---- 1 root uucp 166, 0  3. Nov 16:40 /dev/ttyACM0
       ```
     The owner is right behind root, in my case its "uucp" !
     
- **Enable Read/Write Permission:**
  - ```
    sudo usermod -a -G uucp <YOURUSERNAME>
    ```
    Log out and in again or just reboot your PC.
    
 - Thats all you have to do for your OS Configuration.
  
## Lets code!  
To test that everything is working as intended, lets create the "Hello World" program of all microcontrollers => blinking a LED!
