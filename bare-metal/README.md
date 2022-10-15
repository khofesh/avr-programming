# AVR

```shell
[fahmad@ryzen arduino-uno]$  dnf search avr
Last metadata expiration check: 1:32:23 ago on Sat 08 Oct 2022 01:52:46 PM WIB.
========================= Name & Summary Matched: avr ==========================
avr-binutils.x86_64 : Cross Compiling GNU binutils targeted at avr
avr-gcc.x86_64 : Cross Compiling GNU GCC targeted at avr
avr-gcc-c++.x86_64 : Cross Compiling GNU GCC targeted at avr
avr-libc.noarch : C library for use with GCC on Atmel AVR microcontrollers
avr-libc-doc.noarch : AVR C library docs in html and pdf format
avra.x86_64 : Atmel AVR assembler
avrdude.x86_64 : Software for programming Atmel AVR Microcontroller
[fahmad@ryzen arduino-uno]$  sudo dnf install avr-binutils avr-gcc avr-libc avrdude
```

add `/usr/avr/include/**` to vscode `c_cpp_properties.json`

create the object file from the source code

```shell
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o blink_led.o blink_led.c
```

create the executable

```shell
avr-gcc -mmcu=atmega328p blink_led.o -o blink_led
```

convert the executable to a binary file

```shell
avr-objcopy -O ihex -R .eeprom blink_led blink_led.hex
```

upload the binary file

```shell
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:blink_led.hex
```

result if successful

```shell
[fahmad@ryzen bare-metal]$  make upload
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:blink_led.hex

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably lgt8fx328p)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "blink_led.hex"
avrdude: input file blink_led.hex auto detected as Intel Hex
avrdude: writing flash (176 bytes):

Writing | ################################################## | 100% 0.04s

avrdude: 176 bytes of flash written

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.
```

## Complex Makefile

```shell
make flash_usbasp
```

# Components

- 100 nF (0.1 μF) capacitor
- 10 nF to 1 uF
- LED
- resistor: 200 - 500 ohms
- 2N7000 MOSFET
- A speaker with a DC-blocking capacitor
  around 10 uF
- A USB-Serial adapter
- light-dependent resistors (LDR)

# References

- https://fedoraproject.org/wiki/Packages_For_Embedded_Development
- https://www.hackster.io/milanistef/introduction-to-bare-metal-programming-in-arduino-uno-f3e2b4
- https://stackoverflow.com/questions/48386045/get-avr-with-gcc-running-on-fedora
- https://www.reddit.com/r/arduino/comments/f972l3/new_to_arduino_but_i_want_to_program_baremetal_so/
- https://baremetalmicro.com/tutorial_avr_digital_io/index.html
