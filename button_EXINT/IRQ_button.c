#include "button.h"
#include "lpc17xx.h"
#include "../utils/input.h"

extern volatile Input detectedInputs[];

void EINT0_IRQHandler (void)	  
{
	detectedInputs[0].counter = 1;	/* alert that button has been pressed */
	disableBtn(0);									/* self disable the button (both interrupt and pin) */
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt int0 */
}


void EINT1_IRQHandler (void)	  
{
	detectedInputs[1].counter = 1;	/* alert that button has been pressed */
	disableBtn(1);									/* self disable the button (both interrupt and pin) */
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt key1 */
	
}

void EINT2_IRQHandler (void)	  
{
	detectedInputs[2].counter = 1;	/* alert that button has been pressed */
	disableBtn(2);									/* self disable the button (both interrupt and pin) */
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt key2 */   
}

