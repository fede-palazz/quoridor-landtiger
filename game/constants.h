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
#define BOTTOM_BOARD_Y	TOP_PADDING + (SQUARE_LENGTH + INT_PADDING) * SQUARE_NUM
// TODO
#define BG_COLOR				NO_COLOR
#define TXT_COLOR				BLACK

/* LCD colors */
#define Color 					int16_t
#define WHITE         	0xFFFF
#define BLACK         	0x0000
#define GREY          	0xF7DE
#define BLUE          	0x001F
#define BLUE2         	0x051F
#define RED           	0xF800
#define MAGENTA       	0xF81F
#define GREEN         	0x07E0
#define GREEN_GH				0x8ED7
#define BLUE_GH					0x8EBB
#define RED_GH					0xF90A
#define CYAN          	0x7FFF
#define YELLOW        	0xFFE0
#define DARK_GRAY 			0x4208
#define TRANSPARENT			0x590C
#define NO_COLOR      	-1


#endif


/*

#define MAX_SCREEN_X 240
#define MAX_SCREEN_Y 320

#define SCREEN_CENTER_X MAX_SCREEN_X * 0.5
#define SCREEN_CENTER_Y MAX_SCREEN_Y * 0.5

#define WHITE_COLOR 0xFFFF
#define BLACK_COLOR 0x0000


#define BACKGROUND_COLOR DARK_GRAY

#define RIT_OSCILLATOR_FREQUENCY 100000000 //100 MHz
#define RIT_INTERVAL_IN_MILLISECONDS 50
#define RIT_INTERVAL_IN_CLOCK_COUNT RIT_INTERVAL_IN_MILLISECONDS *(RIT_OSCILLATOR_FREQUENCY / 1000)

#define TIMER_OSCILLATOR_FREQUENCY 25000000 //25MHz
#define ONE_SECOND_FOR_TIMER_IN_CLOCK_COUNT 1 * TIMER_OSCILLATOR_FREQUENCY

*/

