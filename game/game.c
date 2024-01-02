#include "game.h"

void initPlayers(void);

/*
	Convention:
	 - "0" -> nothing there
	 - "1" -> player
	 - "2" -> barrier
*/
static uint8_t board[13][13] = {
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
};
static GameStatus gameStatus = WAITING;
static Player p1, p2;


void initGame() {
	//LCD_Clear(BG_COLOR);							/* Set background color 	*/
	drawBoard(BLACK, NO_COLOR);					/* Board initialization		*/
	initPlayers();											/* Players initialization	*/
	drawInitialLabels();
	drawPlayers(p1, p2);
	drawInitialMessage();
}

void initPlayers() {
	Coordinate initialPosP1 = {6, 0};
	Coordinate initialPosP2 = {6, 12};
	initPlayer(&p1, initialPosP1, GREEN_GH);
	initPlayer(&p2, initialPosP2, RED_GH);
}



