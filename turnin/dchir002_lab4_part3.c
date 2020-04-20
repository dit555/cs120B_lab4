/*	Author: Dumitru Chiriac lab 4
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 4 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State { Start, Locked, Digit1, Unlock} state;
	
void Tick(){
	unsigned char temp = PINA;
	unsigned char temp2 = 0x00;
	switch(state){ //transitions
		case Start: state = Locked; break;
		case Locked: 
			if (temp == 0x00 || temp == 0x80)
			    	state = Locked;
			else if (temp == 0x04)
				state = Digit1;
			break;
		case Digit1:
		       	if ( temp == 0x00)
			       state = Digit1;
			else if (temp == 0x01 || temp == 0x04 || temp == 0x80)
				state = Locked;
			else if (temp == 0x02)
				state = Unlock;	
			break;
		case Unlock:
			if (temp == 0x80)
				state = Locked;
			else
				state = Unlock;
		       	break;
		default: state = Start; break;

	}

	switch(state){
		case Start: break;
		case Locked: temp2 = 0x00; break;
		case Digit1: break;
		case Unlock: temp2 = 0x01; break;
		default: break;

	}
	PORTB = temp2;
}

int main(void) {
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0x00;
		
    	while (1) {
		Tick();
    	}
    	return 1;
}
