#include "input.h"

void readButtonsInputs(void);
void readJoystickInputs(void);


volatile Input detectedInputs[N_BTN + N_JOYSTICK] = {
// Key				 Status  	Counter
	{Int0, 			Released, 	0}, 
	{Key1, 			Released, 	0}, 
	{Key2, 			Released, 	0}, 
	{J_Select, 	Released, 	0}, 
	{J_Down, 		Released, 	0}, 
	{J_Left, 		Released, 	0},
	{J_Right,	 	Released, 	0}, 
	{J_Up, 			Released, 	0}
};


void updateDetectedInputs()
{
	readButtonsInputs();
	readJoystickInputs();
}

void readButtonsInputs() {
	int index;
	// scan buttons values
	for (index = 0; index < N_BTN; index++)
	{		
		if (detectedInputs[index].counter != 0)			/* Button pressed at least once */
		{
			int btnPinPosition = INT0_BTN_PIN_POSITION + index; 					/* Button pins have an ordered position starting from int0 to key2 */
			int btnValue = (LPC_GPIO2->FIOPIN & (1 << btnPinPosition));

			if (btnValue == 0)
			{	/* button pressed */
				detectedInputs[index].action = Pressed;	/* Update button status */
				detectedInputs[index].counter++; 				/* Count how many times the handler was called */
			}
			else
			{ /* button released */
				detectedInputs[index].counter = 0;
				detectedInputs[index].action = Released;
				enableBtn(index);												/* Enable button GPIO and interrupts */
			}
		}
	}
}

void readJoystickInputs() {
	int index;
	// scan joystick values
	//for (index = N_JOYSTICK - 1; index >= 0 ; index--) /* When joystick arrows are used, the simulator press the select at the same time, so we prioritize the arrows by starting from 5 to 0 */
	for (index = 0; index < N_JOYSTICK ; index++)
	{	
		int joystickPinPosition = JOYSTICK_BTN_PIN_POSITION + index; 		/* Joystick pins have an ordered position (select,down,left,right,up) */
		int joystickValue = (LPC_GPIO1->FIOPIN & (1 << joystickPinPosition));
		
		if (joystickValue == 0)					
		{	/* Joystick pressed */
			detectedInputs[index + N_BTN].counter++;
			detectedInputs[index + N_BTN].action = Pressed;
		}
		else
		{ /* Joystick released */
			detectedInputs[index + N_BTN].counter = 0;
			detectedInputs[index + N_BTN].action = Released;
		}
	}
}
