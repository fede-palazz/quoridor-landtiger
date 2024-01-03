#include "button_utils.h"
#include "../game/constants.h"

/*
*	Possible IRQn_Type values:
*  - EINT0_IRQn = 18
*  - EINT1_IRQn = 19
*  - EINT2_IRQn = 20
*
*/
void enableBtn(int btnNum) {
	int pinsel_bit_pos = 20 + btnNum*2;								// PINSEL bit positions should be respectively 20,22,24
	NVIC_EnableIRQ(EINT0_IRQn + btnNum);							// Enable button interrupts
	LPC_PINCON->PINSEL4  |= (1 << pinsel_bit_pos);   	// Enable the pin connection for the button
}

void disableBtn(int btnNum) {
	int pinsel_bit_pos = 20 + btnNum*2;								// PINSEL bit positions should be respectively 20,22,24
	NVIC_DisableIRQ(EINT0_IRQn + btnNum);							// Disable button interrupts
	LPC_PINCON->PINSEL4  &= ~(1 << pinsel_bit_pos);		// Disable the pin connection for the button
}