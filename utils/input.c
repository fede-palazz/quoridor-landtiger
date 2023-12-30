#include "input.h"

int btn_down_counter[N_BTN] = {0};
//volatile int joystick_counter[5] = {0}; /*Ordered as select,down,left,right,up*/

Input get_debounced_button_input()
{
	Input detected_input;
	int index;
	for (index = 0; index < N_BTN; index++)
	{
		if (btn_down_counter[index] != 0)
		{
			int btn_pin_position = INT0_BTN_PIN_POSITION + index; /* Button pins have an ordered position starting from int0 to key2 */
			int btn_value = (LPC_GPIO2->FIOPIN & (1 << btn_pin_position));
			//IRQn_Type btn_interrupt = (IRQn_Type)(EINT0_IRQn + index);

			if (btn_down_counter[index] == 1)
			{ /* if it is the first time we handle it (initially set to 1 by irq handler) */
				detected_input.key = (InputKey)(Int0 + index);
				detected_input.action = Pressed;
				btn_down_counter[index]++;
				return detected_input;
			}

			if (btn_value == 0)
			{							   /* button pressed */
				btn_down_counter[index]++; /* count how many times the handler was called */
			}
			else
			{ /* button released */
				btn_down_counter[index] = 0;
				detected_input.key = (InputKey)(Int0 + index);
				detected_input.action = Released;
				enableBtn(index);
			}
		}
	}
	return detected_input;
}
//Note: joystick should not need debouncing
//Input get_joystick_input()
//{
//	Input detected_input = EMPTY_INPUT;
//	for (int index = 5; index >= 0; index--)
//	{																/* When joystick arrows are used, the simulator press the select at the same time, so we prioritize the arrows by starting from 5 to 0 */
//		int input_pin_position = JOYSTICK_BTN_PIN_POSITION + index; /* Joystick pins have an ordered position (select,down,left,right,up) */
//		int input_value = (LPC_GPIO1->FIOPIN & (1 << input_pin_position));
//		if (input_value == 0)
//		{
//			joystick_counter[index]++;
//			if (joystick_counter[index] == 1)
//			{ /* if it is pressed for the first time */
//				detected_input.key = (InputKey)(JoystickButton + index);
//				detected_input.action = Pressed;
//			}
//			else if (joystick_counter[index] == JOYSTICK_REARM_COUNT)
//			{ /* if it is still pressed for certain time, rearm the joystick*/
//				joystick_counter[index] = 0;
//				detected_input.key = (InputKey)(JoystickButton + index);
//				detected_input.action = Released;
//			}
//			return detected_input;
//		}
//		else if (joystick_counter[index] != 0)
//		{
//			joystick_counter[index] = 0;
//			detected_input.key = (InputKey)(JoystickButton + index);
//			detected_input.action = Released;
//		}
//	}
//	return detected_input;
//}

void debouncer_setup()
{
	int i;
	for (i = 0; i < N_BTN; i++)
	{
		btn_down_counter[i] = 0;
	}
}

Input get_debounced_input()
{
	Input btnInput = get_debounced_button_input();
	return btnInput;
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
}
