/****************************************Copyright (c)****************************************************
**                                      
**                     https://github.com/fede-palazz/quoridor-landtiger
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Federico Palazzi
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            Quoridor game for LandTiger board
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "LPC17xx.h"
#include "RIT/RIT.h"
#include "game/game.h"
#include "utils/input.h"
#include "timer/timer.h"
#include "joystick/joystick.h"
#include "button_EXINT/button.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int main(void)
{
  SystemInit();  									/* System Initialization (i.e., PLL)  */
	BUTTON_init();									/* Buttons Initialization 						*/
	joystick_init();								/* Joystick Initialization 						*/
	init_timer(0, 0x017D7840);			/* Timer0 Initialization (1s)					*/
	init_RIT(0x004C4B40);						/* RIT Initialization (50 ms)       	*/
	enable_RIT();
	LCD_Initialization();						/* LCD display Initialization					*/
	initGame();
	resetDetectedInputs();
  enableInputDetection();
	
	LPC_SC->PCON |= 0x1;						/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		//__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
