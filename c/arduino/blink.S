#define __SFR_OFFSET 0
#include <avr/io.h>

.global main

main:
; Set Port B Bit 5 (Arduino Uno digital pin 13) as output
sbi   DDRB, 5

loop:
; Toggle Port B Bit 5 using PINB toggle feature
sbi   PINB, 5

; Delay loop
ldi   r18, 41
ldi   r19, 150
ldi   r20, 128
delay:
dec   r20
brne  delay
dec   r19
brne  delay
dec   r18
brne  delay

rjmp  loop
