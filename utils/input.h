#ifndef INPUT_H
#define INPUT_H

#include "../utils/datatypes.h"
#include "joystick_handlers.h"
#include "button_handlers.h"
#include "button_utils.h"
#include "lpc17xx.h"

#define N_BTN 											3
#define N_JOYSTICK									5
#define INT0_BTN_PIN_POSITION 			10
#define JOYSTICK_BTN_PIN_POSITION 	25
#define JOYSTICK_REARM_COUNT 				10


extern volatile Input detectedInputs[];
extern void updateDetectedInputs(void);
extern void resetDetectedInputs(void);

#endif
