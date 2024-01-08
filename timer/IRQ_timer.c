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
	/* Zero padding if counter < 10 */
	if (game.countdown < 10) {
		/* Convert countdown value into char array */
		sprintf((char *)countDownBuffer, "0:0%d", game.countdown);
		color = RED_GH;
	}
	else {
		/* Convert countdown value into char array */
		sprintf((char *)countDownBuffer, "0:%d", game.countdown);
	}
	/* Print countdown */
	if (game.turn == 1)
		GUI_Text(COUNT1_OFFSET_X, COUNT_OFFSET_Y, countDownBuffer, color, BG_COLOR);
	else
		GUI_Text(COUNT2_OFFSET_X, COUNT_OFFSET_Y, countDownBuffer, color, BG_COLOR);
  
	/* When time is expired */
	if (game.countdown == 0) {
		/* Current turn is finished	*/
		disableInputDetection();
		disable_timer(0);
		reset_timer(0);
		game.countdown = COUNTDOWN_TIME_S;
		enable_timer(0);
		clearHighlightedSquares();
 		if (game.turn == 2)						/* Override current timer */
			GUI_Text(COUNT2_OFFSET_X, COUNT_OFFSET_Y, (uint8_t *) "     ", TXT_COLOR, BG_COLOR);
		else
			GUI_Text(COUNT1_OFFSET_X, COUNT_OFFSET_Y, (uint8_t *) "     ", TXT_COLOR, BG_COLOR);
		startNewTurn();
		enableInputDetection();
	}
	else
		game.countdown--;
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
