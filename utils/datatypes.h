#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include "stdint.h"

typedef struct coordinate 
{
   uint16_t x;
   uint16_t y;
} Coordinate;

typedef enum input_key
{
	None = -1,
	JoystickButton,
	JoystickDown,
	JoystickLeft,
	JoystickRight,
	JoystickUp,
	Int0,
	Key1,
	Key2
} InputKey;

typedef enum input_action
{
	Pressed,
	Released
} InputAction;

typedef struct input
{
	InputKey key;
	InputAction action;
} Input;
	
#endif
