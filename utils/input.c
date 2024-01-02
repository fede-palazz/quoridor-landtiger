#include "input.h"

void readButtonsInputs(void);
void readJoystickInputs(void);

/*
*	Inputs order: [Int0, Key1, Key2, J_Select, J_Down, J_Left, J_Right, J_Up]
*/
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
	for (index = N_BTN; index < N_BTN + N_JOYSTICK; index++) 
	{	
		
	}
}

//Note: joystick should not need debouncing
//Input get_joystick_input()
//{
//	Input detectedInput = EMPTY_INPUT;
//	for (int index = N_JOYSTICK; index >= 0; index--)
//	{																/* When joystick arrows are used, the simulator press the select at the same time, so we prioritize the arrows by starting from 5 to 0 */
//		int input_pin_position = JOYSTICK_BTN_PIN_POSITION + index; /* Joystick pins have an ordered position (select,down,left,right,up) */
//		int input_value = (LPC_GPIO1->FIOPIN & (1 << input_pin_position));
//		if (input_value == 0)
//		{
//			joystickCounter[index]++;
//			if (joystickCounter[index] == 1)
//			{ /* if it is pressed for the first time */
//				detectedInput.key = (InputKey)(J_Select + index);
//				detectedInput.action = Pressed;
//			}
//			else if (joystickCounter[index] == JOYSTICK_REARM_COUNT)
//			{ /* if it is still pressed for certain time, rearm the joystick*/
//				joystickCounter[index] = 0;
//				detectedInput.key = (InputKey)(J_Select + index);
//				detectedInput.action = Released;
//			}
//			return detectedInput;
//		}
//		else if (joystickCounter[index] != 0)
//		{
//			joystickCounter[index] = 0;
//			detectedInput.key = (InputKey)(J_Select + index);
//			detectedInput.action = Released;
//		}
//	}
//	return detectedInput;
//}

//void debouncer_setup()
//{
//	int i;
//	for (i = 0; i < N_BTN; i++)
//	{
//		btnCounter[i] = 0;
//	}
//}

//Input get_debounced_input()
//{
//	Input btnInput = get_debounced_button_input();
//	return btnInput;
//	Input joystick_input = get_joystick_input();
//	Input button_input = get_debounced_button_input();
//	if (joystick_input.key != None)
//	{
//		return joystick_input;
//	}
//	else
//	{
//		return button_input;
//	}
//}
