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

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile Input last_detected_input;

void RIT_IRQHandler(void) {
  Input input = get_debounced_input();
  last_detected_input = input;


  disable_RIT();
  reset_RIT();
  enable_RIT();
  LPC_RIT->RICTRL |= 0x1; /* clear interrupt flag */

  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
