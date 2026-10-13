#define __SFR_OFFSET 0
#include <avr/io.h>

.global main

main:
	;   Set PB5 (Digital Pin 2 ) as output
	sbi DDRB, 0
	sbi DDRB, 1

	sbi DDRD, 2
	sbi DDRD, 3
	sbi DDRD, 4
	sbi DDRD, 5
	sbi DDRD, 6
	sbi DDRD, 7

decode_start:
	ldi r29, 8
	inc r29

	ldi r31, 1

loop:

	;    copy the recoded byte to two seperate bytes mask them for portb and portd and out them
	mov  r30, r31
	mov  r28, r31
	andi r30, 0b00000011
	out  PORTB, r30
	andi r28, 0b11111100
	out  PORTD, r31

	;    shift left the decoded byte and decrement counter and jump to end if zero
	dec  r29
	breq decode_start
	lsl  r31

	;   ~0.5s Delay loop at 16MHz
	ldi r18, 41
	ldi r19, 150
	ldi r20, 128

delay:
	dec  r20
	brne delay
	dec  r19
	brne delay
	dec  r18
	brne delay

	rjmp loop

end:
	nop
