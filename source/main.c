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

enum State { Start, A_Np, B_P, B_Np, A_P } state;
	
void Tick(){
	unsigned char temp = PINA;
	unsigned char temp2 = 0x00;
	switch(state){ //transitions
		case Start: state = A_Np; break;
		case A_Np: state = temp ? B_P : A_Np; break;
		case B_P: state = temp ? B_P : B_Np; break;
		case B_Np: state = temp ? A_P : B_Np; break;
		case A_P: state = temp ? A_P : A_Np; break;
		default: state = Start; break;

	}

	switch(state){
		case A_Np: temp2 = 0x01; break;
		case B_P: temp2 = 0x02; break;
		case B_Np: temp2 = 0x02; break;
		case A_P: temp2 = 0x01; break;
		default: break;

	}
	PORTB = temp2;
}

int main(void) {
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0x00; PORTA = 0x00;
		
    	while (1) {
		Tick();
    	}
    	return 1;
}
