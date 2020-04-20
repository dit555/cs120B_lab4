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

enum State { Start, Wait, Inc, Inc2, Dec, Dec2, Reset, Reset2} state;
	
void Tick(){
	unsigned char temp = PINA;
	unsigned char temp2 = PORTC;
	switch(state){ //transitions
		case Start: temp2 = 0x07; state = Wait; break;
		case Wait: 
			if (temp == 0x01){
			    	state = Inc;
				if(temp != 9) temp2++;
			}
			else if (temp == 0x02){
				state = Dec;
				if(temp > 0) temp2--;
			}
			else if (temp == 0x03)
				state = Reset;
			else
				state = Wait;
			break;
		case Inc2: state = Wait; break;
		case Inc: state = (temp == 0x01) ? Inc : Inc2; break;
		case Dec2: state = Wait; break;
		case Dec: state = (temp == 0x02) ? Dec : Dec2; break;
		case Reset: state = Reset2; break;
		case Reset2: state = (temp == 0x03) ? Reset : Wait; break;
		default: state = Start; break;

	}

	switch(state){
		case Start: break;
		case Wait: break;
		case Dec2: break;
		case Inc2: break;
		case Reset: temp2 = 0x00; break;
		default: break;

	}
	PORTC = temp2;
}

int main(void) {
	DDRA = 0x00; PORTA = 0x00;
	DDRC = 0x00; PORTC = 0x00;
		
    	while (1) {
		Tick();
    	}
    	return 1;
}
