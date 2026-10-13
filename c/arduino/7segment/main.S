#define __SFR_OFFSET 0
#include <avr/io.h>

.global main

main:
    ; Set PB5 (Digital Pin 2 ) as output
    sbi   DDRD, 0
    sbi   DDRD, 1
    sbi   DDRD, 2
    sbi   DDRD, 3
    sbi   DDRD, 4
    sbi   DDRD, 5
    sbi   DDRD, 6


decode_start:
    ldi r29, 8
    inc r29

    ldi r31, 1

loop:
    ; shift left the decoded byte and decrement counter and jump to end if zero
    dec r29
    breq decode_start 
    lsl r31

    out PORTD, r31

    ; ~0.5s Delay loop at 16MHz
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
 
end:
    nop
