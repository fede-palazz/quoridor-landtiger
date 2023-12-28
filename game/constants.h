#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "stdint.h"

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

/* LCD colors */
#define Color 				int16_t
#define WHITE         0xFFFF
#define BLACK         0x0000
#define GREY          0xF7DE
#define BLUE          0x001F
#define BLUE2         0x051F
#define RED           0xF800
#define MAGENTA       0xF81F
#define GREEN         0x07E0
#define GREEN_GH			0x8ED7
#define BLUE_GH				0x8EBB
#define RED_GH				0xF90A
#define CYAN          0x7FFF
#define YELLOW        0xFFE0
#define NO_COLOR      -1

typedef struct POINT 
{
   uint16_t x;
   uint16_t y;
} Coordinate;

#endif
