#include "game.h"

void initPlayers(void);

/*
	Convention:
	 - "0" -> nothing there
	 - "1" -> player
	 - "2" -> barrier
*/
static uint8_t board[BOARD_SIZE][BOARD_SIZE] = {
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
volatile Game game;
static Player p1, p2;
static Coordinate possibleMoves[4];


void initGame() {
	game.status = WAITING;							/* Game initialization		*/
	//LCD_Clear(BG_COLOR);							/* Set background color 	*/
	drawBoard(BLACK, NO_COLOR);					/* Board initialization		*/
	initPlayers();											/* Players initialization	*/
	drawInitialLabels();
	drawPlayers(p1, p2);
	drawInitialMessage();
}

void initPlayers() {
	Coordinate initialPosP1 = {6, 12};
	Coordinate initialPosP2 = {6, 0};
	initPlayer(&p1, initialPosP1, GREEN_GH);
	initPlayer(&p2, initialPosP2, RED_GH);
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

void findPossibileMoves(Coordinate startPos) {
	int i;
	Coordinate endPos;
	Coordinate middlePos;
	
	for (i=0; i<4; i++) {
		switch((Movement) i) {		/* Compute end and middle positions */
			case MOV_UP:
				/* Check UP square */
				endPos.x = startPos.x;
				endPos.y = startPos.y - 2;
				middlePos.x = startPos.x;
				middlePos.y = startPos.y - 1;
				break;
			case MOV_DOWN:
				/* Check DOWN square */
				endPos.x = startPos.x;
				endPos.y = startPos.y + 2;
				middlePos.x = startPos.x;
				middlePos.y = startPos.y + 1;
				break;
			case MOV_RIGHT:
				/* Check RIGHT square */
				endPos.x = startPos.x + 2;
				endPos.y = startPos.y;
				middlePos.x = startPos.x + 1;
				middlePos.y = startPos.y;
				break;
			case MOV_LEFT:
				/* Check LEFT square */
				endPos.x = startPos.x - 2;
				endPos.y = startPos.y;
				middlePos.x = startPos.x - 1;
				middlePos.y = startPos.y;
				break;
		}
		/* Check if move can be made */
		if (isValidSquare(endPos) && isEmptySquare(endPos) && !isBarrierSquare(middlePos)) {
			possibleMoves[i].x = endPos.x;
			possibleMoves[i].y = endPos.y;
		}
		else {
			/* Assign invalid values */
			possibleMoves[i].x = BOARD_SIZE + 1;
			possibleMoves[i].y = BOARD_SIZE + 1;
		}
	}
}

void highlightSquares() {
	int i = 0;
	if (game.turn == 1) {
		/* Highlight P1 possibile moves */
			findPossibileMoves(p1.pos);
	}
	else {
		/* Highlight P2 possibile moves */
		findPossibileMoves(p2.pos);
	}
	for (i=0; i<4; i++) {		
		if (possibleMoves[i].x < BOARD_SIZE) /* Highlight only valid squares */
			fillSquare(possibleMoves[i], HIGHLIGHT_COLOR);
	}
}



