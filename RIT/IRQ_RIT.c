/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "../utils/input.h"
#include "lpc17xx.h"
#include "RIT.h"

//#define INT0 			detectedInputs[0]
//#define KEY1 			detectedInputs[1]
//#define KEY2 			detectedInputs[2]
//#define J_SELECT 	detectedInputs[3]
//#define J_DOWN 		detectedInputs[4]
//#define J_LEFT 		detectedInputs[5]
//#define J_RIGHT 	detectedInputs[6]
//#define J_UP 			detectedInputs[7]

extern volatile Input detectedInputs[];
int i;
Input input;

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void RIT_IRQHandler(void) {
	// Update inputs status
	updateDetectedInputs();
	
	// Scan buttons values
	for (i=0; i<N_BTN; i++) {
		input = detectedInputs[i];
		if (input.counter > 1) {
			// Button has been pressed
			switch(input.key) {
				case Int0:
					onPressInt0();					/* Handle Int0 Pressure */
					break;
				case Key1:
					onPressKey1();					/* Handle Key1 Pressure */
					break;
				case Key2:
					onPressKey2();					/* Handle Key2 Pressure */
					break;
				default:
					break;
			}
		}
	}
	
	// TODO: scan joystick values

  disable_RIT();
  reset_RIT();
  enable_RIT();
  LPC_RIT->RICTRL |= 0x1; /* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
