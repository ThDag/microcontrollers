avr-gcc -mmcu=atmega328p -Wall -Os -o main.elf main.S && \
avr-objcopy -O ihex -R .eeprom main.elf main.hex && \
avrdude -c arduino -p m328p -P /dev/tty.usbserial-110 -b 115200 -U flash:w:main.hex:i
