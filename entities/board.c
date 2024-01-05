#include "board.h"

/*
	Convention:
	 - "0" -> nothing there
	 - "1" -> player
	 - "2" -> barrier
*/
static uint8_t board[BOARD_SIZE][BOARD_SIZE] = {
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
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void initBoard(Coordinate p1Pos, Coordinate p2Pos) {
	int i,j;
	for (i=0; i<BOARD_SIZE; i++)
		for (j=0; j<BOARD_SIZE; j++)
			board[i][j] = EMPTY_SQUARE;
	/* Set players' initial coordinates */
	board[p1Pos.y][p1Pos.x] = PLAYER_SQUARE;
	board[p2Pos.y][p2Pos.x] = PLAYER_SQUARE;
}

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

void updateBoardPlayer(Player* player) {
	/* Remove player from old position */
	board[player->previousPos.y][player->previousPos.x] = EMPTY_SQUARE;
	/* Move player to new position */
	board[player->pos.y][player->pos.x] = PLAYER_SQUARE;
}
