/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
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
	LCD_Initialization();						/* LCD display Initialization					*/
	init_timer(0, 0x017D7840);			/* Timer0 Initialization (1s)					*/
	//init_RIT(0x004C4B40);						/* RIT Initialization (50 msec)      	*/
	//initGame();
	enable_timer(0);
	//resetDetectedInputs();
  //enable_RIT();
  //NVIC_SetPriority(RIT_IRQn, 3);
  // NVIC_SetPriority(TIMER0_IRQn, 2);
  //NVIC_SetPriority(TIMER1_IRQn, 1);

	

	// max 30 chars in a row
	//GUI_Text(0, 305, (uint8_t *) "no more walls, move the token", BLUE, WHITE);
	
	
	
	
	
	
	
	
	
	
	
	//GUI_Text(0, 305, (uint8_t *) " touch here : 1 sec to clear  ", BLUE, WHITE);
	//LCD_DrawLine(0, 0, 200, 200, WHITE);
	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */
	//init_timer(0, 0x6108 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	//init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */
	//init_timer(0, 0xC8 ); 						    /* 8us * 25MHz = 200 ~= 0xC8 */
	
	//enable_timer(0);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		//__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
