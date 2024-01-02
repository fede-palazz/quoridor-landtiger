/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../graphics/renderer.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
static int counter = 0;
uint8_t buffer[10];

    // Converte il numero in una stringa di caratteri usando sprintf
    

void TIMER0_IRQHandler (void)
{
	sprintf((char *)buffer, "%d", counter++);						/* Convert number to char array */
	GUI_Text(30,50,(uint8_t *) buffer, BLACK, WHITE);
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
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
