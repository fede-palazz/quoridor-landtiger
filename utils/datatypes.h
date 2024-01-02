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
	Int0,
	Key1,
	Key2,
	J_Select,
	J_Down,
	J_Left,
	J_Right,
	J_Up
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
	uint16_t counter;
} Input;
	
#endif
