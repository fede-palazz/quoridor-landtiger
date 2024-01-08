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

void updateBoardBarrier(Coordinate centrePos, Direction direction) {
	board[centrePos.y][centrePos.x] = BARRIER_SQUARE;
	if (direction == HORIZONTAL) {
		board[centrePos.y][centrePos.x + 1] = BARRIER_SQUARE;
		board[centrePos.y][centrePos.x - 1] = BARRIER_SQUARE;
	}
	else {
		board[centrePos.y + 1][centrePos.x] = BARRIER_SQUARE;
		board[centrePos.y - 1][centrePos.x] = BARRIER_SQUARE;
	}
}

uint8_t isValidBarrierSquare(Coordinate centrePos, Direction direction) {
	Coordinate h1, h2, v1, v2;
	/* If direction horizontal */
	h1.x = centrePos.x + 1;
	h1.y = centrePos.y;
	h2.x = centrePos.x - 1;
	h2.y = centrePos.y;
	
	/* If direction vertical */
	v1.x = centrePos.x;
	v1.y = centrePos.y + 1;
	v2.x = centrePos.x;
	v2.y = centrePos.y - 1;
	
	return direction == HORIZONTAL ? isValidSquare(h1) && isValidSquare(h2)
																 : isValidSquare(v1) && isValidSquare(v2);
}

uint8_t isBarrierOverlapping(Coordinate centrePos, Direction direction) {
	Coordinate h1, h2, v1, v2;
	if (isBarrierSquare(centrePos))		/* Check overlapping of barrier central position */
		return 1;
	/* If direction horizontal */
	h1.x = centrePos.x + 1;
	h1.y = centrePos.y;
	h2.x = centrePos.x - 1;
	h2.y = centrePos.y;
	
	/* If direction vertical */
	v1.x = centrePos.x;
	v1.y = centrePos.y + 1;
	v2.x = centrePos.x;
	v2.y = centrePos.y - 1;
	
	return direction == HORIZONTAL ? isBarrierSquare(h1) || isBarrierSquare(h2)
																 : isBarrierSquare(v1) || isBarrierSquare(v2);
}
