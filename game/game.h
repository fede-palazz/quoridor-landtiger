#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h" 

/* DISPLAY CONFIG				*/
#define LCD_WIDTH 			240
#define LCD_HEIGHT			320

/* BOARD CONFIG					*/
#define SQUARE_NUM			7
#define TOP_PADDING			50
#define LAT_PADDING			5
#define	INT_PADDING			5
#define SQUARE_BORDERS	2
#define SQUARE_LENGTH 	(LCD_WIDTH - LAT_PADDING * 2 - (INT_PADDING * (SQUARE_NUM - 1))) / SQUARE_NUM

void drawBoard(Color outlineColor, Color fillColor);

#endif
