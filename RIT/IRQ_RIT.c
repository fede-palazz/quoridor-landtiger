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
#include "../utils/button_handlers.h"
#include "../utils/joystick_handlers.h"
#include "lpc17xx.h"
#include "RIT.h"


/*
*	Inputs order: [Int0, Key1, Key2, J_Select, J_Down, J_Left, J_Right, J_Up]
*/
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
		if (input.counter == 2) {			/* Avoid long pressures */
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
	// Scan joystick values
	for (i=N_BTN; i<N_BTN + N_JOYSTICK; i++) {
		input = detectedInputs[i];
		if (input.counter == 1) {			/* Avoid long pressures */
			// Joystick has been used
			switch(input.key) {
				case J_Select:
					onJoystickSelect();			/* Handle Select Pressure */
					break;
				case J_Down:
					onJoystickDown();				/* Handle Joystick Down */
					break;
				case J_Left:
					onJoystickLeft();				/* Handle Joystick Left */
					break;
				case J_Right:
					onJoystickRight();			/* Handle Joystick Right */
					break;
				case J_Up:
					onJoystickUp();					/* Handle Joystick Up */
					break;
				default:
					break;
			}
		}
	}
  //disable_RIT();
  reset_RIT();
  //enable_RIT();
  LPC_RIT->RICTRL |= 0x1; /* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
