/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "../graphics/renderer.h"
#include "../utils/input.h"
#include "../game/game.h"
#include "lpc17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

uint8_t countDownBuffer[10];
    

void TIMER0_IRQHandler (void)
{
	Color color = TXT_COLOR;
	disableInputDetection();			/* Disable RIT and buttons */

//	if (game.countdown > 20)				/* Underflow condition */
//		return;
	if (game.countdown == 20) {
		/* A new turn has started	*/
		if (game.turn == 1)						/* Override P2 timer */
			GUI_Text(LAT_PADDING + 162, LAT_PADDING + 22, (uint8_t *) "    ", BG_COLOR, BG_COLOR);
		else
			GUI_Text(LAT_PADDING + 30, LAT_PADDING + 22, (uint8_t *) "    ", BG_COLOR, BG_COLOR);
	}
	/* Zero padding if counter < 10 */
	if (game.countdown < 10) {
		/* Convert countdown value into char array */
		sprintf((char *)countDownBuffer, "0:0%d", game.countdown--);
		color = RED_GH;
	}
	else {
		/* Convert countdown value into char array */
		sprintf((char *)countDownBuffer, "0:%d", game.countdown--);
	}
	/* Print countdown */
	if (game.turn == 1)
		GUI_Text(LAT_PADDING + 30, LAT_PADDING + 22, countDownBuffer, color, BG_COLOR);
	else
		GUI_Text(LAT_PADDING + 162, LAT_PADDING + 22, countDownBuffer, color, BG_COLOR);
  
	if (game.countdown == 0) {
		/* Current turn is finished	*/
		disable_timer(0);
		reset_timer(0);
		skipTurn();
		enable_timer(0);
	}
	enableInputDetection();				/* Enable RIT and buttons */
	LPC_TIM0->IR = 1;							/* Clear interrupt flag */
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/