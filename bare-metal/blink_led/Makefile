CC = avr-gcc
TTY_PATH = /dev/ttyACM0
MCU = atmega328p

all: blink_led.o blink_led blink_led.hex

blink_led.hex: blink_led
	avr-objcopy -O ihex -R .eeprom $^ $@

blink_led: blink_led.o
	$(CC) -mmcu=$(MCU) $^ -o $@

blink_led.o: blink_led.c
	$(CC) -Os -DF_CPU=16000000UL -mmcu=$(MCU) -c -o $@ $^

upload:
	avrdude -F -V -c arduino -p $(MCU) -b 19200 -P /dev/ttyACM0 -U flash:w:blink_led.hex

clean:
	rm blink_led blink_led.hex blink_led.o