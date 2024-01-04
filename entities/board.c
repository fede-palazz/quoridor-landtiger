#include "board.h"

/*
	Convention:
	 - "0" -> nothing there
	 - "1" -> player
	 - "2" -> barrier
*/
volatile uint8_t board[BOARD_SIZE][BOARD_SIZE] = {
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


uint8_t isValidSquare(Coordinate squarePos) {
	if (squarePos.x < BOARD_SIZE && squarePos.y < BOARD_SIZE)
		return 1;
	return 0;
}

uint8_t isEmptySquare(Coordinate squarePos) {
	if (board[squarePos.y][squarePos.x] == EMPTY_SQUARE)
		return 1;
	return 0;
}

uint8_t isPlayerSquare(Coordinate squarePos) {
	if (board[squarePos.y][squarePos.x] == PLAYER_SQUARE)
		return 1;
	return 0;
}

uint8_t isBarrierSquare(Coordinate squarePos) {
	if (board[squarePos.y][squarePos.x] == BARRIER_SQUARE)
		return 1;
	return 0;
}