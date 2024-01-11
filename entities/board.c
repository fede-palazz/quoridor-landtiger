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

void insertBoardBarrier(Coordinate centrePos, Direction direction) {
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

void deleteBoardBarrier(Coordinate centrePos, Direction direction) {
	board[centrePos.y][centrePos.x] = EMPTY_SQUARE;
	if (direction == HORIZONTAL) {
		board[centrePos.y][centrePos.x + 1] = EMPTY_SQUARE;
		board[centrePos.y][centrePos.x - 1] = EMPTY_SQUARE;
	}
	else {
		board[centrePos.y + 1][centrePos.x] = EMPTY_SQUARE;
		board[centrePos.y - 1][centrePos.x] = EMPTY_SQUARE;
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

/*
* Check if a player is blocked after placing a barrier
*/
uint8_t isBarrierBlockingPlayer(Barrier barrier, Coordinate playerPos, uint8_t currentTurn) {
	int i, j;
	int counter = 0;		/* Count how many times a "1" has been placed within an iteration 			*/
	int endRow = currentTurn == 1 ? 0 : SQUARE_NUM - 1;
	int tempRow = -1;
	uint8_t matrix[SQUARE_NUM][SQUARE_NUM] = {0}; /* Declare temporary matrix								*/
	
	matrix[playerPos.y / 2][playerPos.x / 2] = 1; /* Set current player position in the matrix 	*/
	insertBoardBarrier(barrier.centrePos, barrier.direction);		/* Temporary insert the barrier */
	
	do {
		counter = 0; 			/* Reset counter */
		for (i=0; i<SQUARE_NUM; i++) {
			for (j=0; j<SQUARE_NUM; j++) {
				if (matrix[i][j] == 1) {		/* Found a square to be analyzed */
					tempRow = i;		/* Found a "1" within current row */
					if (tempRow == endRow) {
						deleteBoardBarrier(barrier.centrePos, barrier.direction);		/* Delete placed barrier */
						return 0;		/* Player is not trapped */
					}
					/* CASE MOV_LEFT */
					if (j >= 1 && matrix[i][j-1] != 2 && 
							board[i*2][(j*2)-1] != BARRIER_SQUARE ) { /* If left cell is not a wall */
								matrix[i][j-1] = 1;
								counter++;		/* Increment placed ones counter */
					}
					/* CASE MOV_RIGHT */
					if (j <= SQUARE_NUM-2 && matrix[i][j+1] != 2 && 
							board[i*2][(j*2)+1] != BARRIER_SQUARE ) { /* If right cell is not a wall */
								matrix[i][j+1] = 1;
								counter++;		/* Increment placed ones counter */
					}
					/* CASE MOV_UP */
					if (i >= 1 && matrix[i-1][j] != 2 && 
							board[(i*2)-1][j*2] != BARRIER_SQUARE ) { /* If up cell is not a wall */
								matrix[i-1][j] = 1;
								counter++;		/* Increment placed ones counter */
					}
					/* CASE MOV_DOWN */
					if (i <= SQUARE_NUM-2 && matrix[i+1][j] != 2 && 
							board[(i*2)+1][j*2] != BARRIER_SQUARE ) { /* If up cell is not a wall */
								matrix[i+1][j] = 1;
								counter++;		/* Increment placed ones counter */
					}
					matrix[i][j] = 2;		/* Set the square as checked */
				}
			}
		}
	}
	while(counter != 0);
	deleteBoardBarrier(barrier.centrePos, barrier.direction);		/* Delete placed barrier */
	return 1;		/* Player is trapped 		 */
}
