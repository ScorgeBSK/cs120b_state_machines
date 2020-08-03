/*	Author: Trung Lam
 *  Partner(s) Name: 
 *	Lab Section: B22
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, init, poundPress, poundRelease, yKeyPressed, doorUnlock, doorLock} state;

void tick(){
	unsigned char poundButton = PINA & 0x04;
	unsigned char yButton = PINA & 0x02;
	unsigned char xButton = PINA & 0x01;
	unsigned char lockButton = PINA & 0x80;
	unsigned char door = PINB;
	
	switch(state){
		case start:
			state = init;
			break;
		case init:
			state = poundButton ? poundPress : init;
			break;
		case poundPress:
			state = poundButton ? poundPress : poundRelease;
			break;
		case poundRelease:
			state = yButton ? yKeyPressed : poundRelease;
		       break;
	        case yKeyPressed:
		       	state = doorUnlock;
	 		break;
		case doorUnlock:
			state = lockButton ? doorLock : doorUnlock;
			break;		
		case doorLock:
			state = init;
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case init:
			door = 0;
			break;
		case poundPress:
			break;
		case poundRelease:
			break;
		case yKeyPressed:
			break;
		case doorUnlock:
			door = 1;
			break;
		case doorLock:
			door = 0;
			break;
		default:
			break;
        }

	PORTB = door;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
