#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "stdint.h"

/* DISPLAY CONFIG					*/
#define LCD_WIDTH 				240
#define LCD_HEIGHT				320

/* BOARD CONFIG						*/
#define SQUARE_NUM				7
#define TOP_PADDING				45
#define LAT_PADDING				5
#define	INT_PADDING				5
#define SQUARE_BORDERS		2
#define SQUARE_LENGTH 		(LCD_WIDTH - LAT_PADDING * 2 - (INT_PADDING * (SQUARE_NUM - 1))) / SQUARE_NUM
#define BOTTOM_BOARD_Y		TOP_PADDING + (SQUARE_LENGTH + INT_PADDING) * SQUARE_NUM
#define COUNT1_OFFSET_X		LAT_PADDING + 30	
#define COUNT2_OFFSET_X		LAT_PADDING + 162	
#define COUNT_OFFSET_Y		LAT_PADDING + 20

/* GAME CONFIG						*/
#define COUNTDOWN_TIME_S	20
#define BOARD_SIZE				13
#define EMPTY_SQUARE			0
#define PLAYER_SQUARE			1
#define BARRIER_SQUARE		2
#define INITIAL_TURN			1
#define BARRIER_NUM				8

/* LCD colors */
#define Color 						uint16_t
#define WHITE         		0xFFFF
#define BLACK         		0x0000
#define GREY          		0xF7DE
#define BLUE          		0x001F
#define BLUE2         		0x051F
#define RED           		0xF800
#define MAGENTA       		0xF81F
#define GREEN         		0x07E0
#define GREEN_GH					0x8ED7
#define BLUE_GH						0x8EBB
#define GRAY_GH						0x8472
#define RED_GH						0xF90A
#define WHITE_GH					0xE77E
#define CYAN          		0x7FFF
#define YELLOW        		0xFFE0
#define DARK_GRAY 				0x4208
#define TRANSPARENT				0x590C

/* Game elements colors */
#define BG_COLOR					0x0882
#define SQUARE_COLOR			BG_COLOR
#define BORDER_COLOR			0x8472
#define TXT_COLOR					0xCE9B
#define TXT_COLOR_2				0x5B2D
#define HIGHLIGHT_COLOR		0x31C8
#define SELECT_COLOR			WHITE_GH
#define NEW_BARR_COLOR		WHITE_GH
#define BARRIER_COLOR			RED
#define BARRIER_BG_COLOR  BG_COLOR
#define NO_COLOR      		0xCCCC


#endif
