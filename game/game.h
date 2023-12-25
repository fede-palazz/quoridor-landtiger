#ifndef GAME_H
#define GAME_H

//#include "LPC17xx.h"
#include "../graphics/renderer.h"
//#include "../TouchPanel/TouchPanel.h"
//#include "../GLCD/GLCD.h" 

/* DISPLAY CONFIG			*/
#define LCD_WIDTH 		240
#define LCD_HEIGHT		320

/* BOARD CONFIG				*/
#define SQUARE_NUM		7
#define TOP_PADDING		50
#define LAT_PADDING		5
#define	INT_PADDING		5

void drawBoard(Color outlineColor, Color fillColor, uint16_t borders);

#endif
