CC = avr-gcc
TTY_PATH = /dev/ttyACM0

all: blink_led.o blink_led blink_led.hex

blink_led.hex: blink_led
	avr-objcopy -O ihex -R .eeprom $^ $@

blink_led: blink_led.o
	$(CC) -mmcu=atmega328p $^ -o $@

blink_led.o: blink_led.c
	$(CC) -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $@ $^

upload:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(TTY_PATH) -b 115200 -U flash:w:blink_led.hex

clean:
	rm blink_led blink_led.hex blink_led.o