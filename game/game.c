#include "game.h"

void initGame(void);
void initPlayers(void);
void findPossibileMoves(Coordinate startPos);
void highlightSquares(void);
void clearHighlightedSquares(void);
void selectSquare(Movement movement);
void startNewTurn(void);


volatile Game game;
static Player p1, p2;
Player* currentPlayer;
volatile Coordinate possibleMoves[4] = { 
	{BOARD_SIZE, BOARD_SIZE}, 
	{BOARD_SIZE, BOARD_SIZE}, 
	{BOARD_SIZE, BOARD_SIZE}, 
	{BOARD_SIZE, BOARD_SIZE}
};
int8_t selectedSquare = -1;
volatile Barrier barrier;
static Barrier barriers[BARRIER_NUM];
uint8_t placedBarriers = 0;


void initGame() {
	game.status = WAITING;							/* Game initialization		*/
	//LCD_Clear(BG_COLOR);							/* Set background color 	*/
	drawBoard(BLACK, NO_COLOR);					/* Board initialization		*/
	initPlayers();											/* Players initialization	*/
	drawInitialLabels();
	drawPlayers(&p1, &p2);
	drawInitialMessage();
}

void initPlayers() {
	/* Set players' coordinates */
	Coordinate initialPosP1 = {6, 12};
	Coordinate initialPosP2 = {6, 0};
	initPlayer(&p1, initialPosP1, GREEN_GH, BARRIER_NUM);
	initPlayer(&p2, initialPosP2, RED_GH, BARRIER_NUM);
	initBoard(initialPosP1, initialPosP2);
	/* Update current player */
	currentPlayer = INITIAL_TURN == 1 ? &p1 : &p2;
}

/*
* Search for available squares
*/
void findPossibileMoves(Coordinate startPos) {
	int i;
	Coordinate endPos;
	Coordinate middlePos;
	/* Compute end and middle positions */
	for (i=0; i<4; i++) {
		switch((Movement) i) {		
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
			case MOV_LEFT:
				/* Check LEFT square */
				endPos.x = startPos.x - 2;
				endPos.y = startPos.y;
				middlePos.x = startPos.x - 1;
				middlePos.y = startPos.y;
				break;
			case MOV_RIGHT:
				/* Check RIGHT square */
				endPos.x = startPos.x + 2;
				endPos.y = startPos.y;
				middlePos.x = startPos.x + 1;
				middlePos.y = startPos.y;
				break;
		}
		/* Check if move can be made */
		if (isValidSquare(endPos) && !isBarrierSquare(middlePos)) { 
				if (isEmptySquare(endPos) ) {			/* Free square */
					possibleMoves[i].x = endPos.x;
					possibleMoves[i].y = endPos.y;
				}
				else {														/* There is a player */
					/* Increase both middle and end positions */
					switch ((Movement) i) {
						case MOV_UP:
							endPos.y -= 2;
							middlePos.y--;
							break;
						case MOV_DOWN:
							endPos.y += 2;
							middlePos.y++;
							break;
						case MOV_LEFT:
							endPos.x -= 2;
							middlePos.x--;
							break;
						case MOV_RIGHT:
							endPos.x += 2;
							middlePos.x++;
							break;
					}
					/* Check conditions again */
					if (isValidSquare(endPos) && !isBarrierSquare(middlePos) &&
							isEmptySquare(endPos)) {
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
		else {
			/* Assign invalid values */
			possibleMoves[i].x = BOARD_SIZE + 1;
			possibleMoves[i].y = BOARD_SIZE + 1;
		}
	}
}

/*
*	Highlight possible moves that a player can perform
*/
void highlightSquares() {
	int i;
	findPossibileMoves((*currentPlayer).pos);		/* Search possibile moves from player's current position */
	
	for (i=0; i<4; i++) {		
		if (isValidSquare(possibleMoves[i])) 			/* Highlight only valid squares */
			fillSquare(possibleMoves[i], HIGHLIGHT_COLOR);
	}
}

/*
*	Restore previous squares color
*/
void clearHighlightedSquares() {
	int i;
	for (i=0; i<4; i++) {		
		if (isValidSquare(possibleMoves[i])) 			/* Highlight only valid squares */
			fillSquare(possibleMoves[i], SQUARE_COLOR);
	}
}

/*
* Select a square when the player moves the joystick
*/
void selectSquare(Movement movement) {
	if (!isValidSquare(possibleMoves[movement]))
		return;
	if (selectedSquare != -1)
		fillSquare(possibleMoves[selectedSquare], HIGHLIGHT_COLOR);			/* Repaint old selected square   */
	fillSquare(possibleMoves[movement], SELECT_COLOR);								/* Highlight new selected square */
	selectedSquare = movement;																				/* Save selected square index 	 */
}

void startNewTurn() {
	/* Change turn settings */
	if (game.turn == 1) {
		/* Switch to 2nd player */
		currentPlayer = &p2;
		game.turn = 2;
	}
	else {
		/* Switch to 1st player */
		currentPlayer = &p1;
		game.turn = 1;
	}
	/* Check if a barrier needs to be deleted */
	if (game.status == PLACING)
		deleteBarrier(barrier);
	game.status = MOVING;
	selectedSquare = -1;							/* Reset selected square value 			*/
	highlightSquares();								/* Highlight other player's squares */
}

void movePlayer() {
	/* Update player position */
	setPlayerPos(currentPlayer, possibleMoves[selectedSquare].x, possibleMoves[selectedSquare].y);
	/* Update board status */
	updateBoardPlayer(currentPlayer);
	/* Draw player in new position */
	drawNewPlayerPos(currentPlayer);
}

void createNewBarrier() {
	clearHighlightedSquares();
	selectedSquare = -1;
	/* Initialize new barrier */
	barrier.centrePos.x = 7;
	barrier.centrePos.y = 5;
	barrier.direction = HORIZONTAL;
	barrier.color = NEW_BARR_COLOR;		
	/* Draw new barrier */
	drawBarrier(barrier);			// TODO: change barrier color according to current player
}

void deleteNewBarrier() {
	barrier.color = WHITE;		// TODO: change with board bg color
	/* Draw new barrier */
	drawBarrier(barrier);
}

void moveBarrier(Movement movement) {
	Coordinate newPos = barrier.centrePos;
	switch(movement) {
		case MOV_UP:
			newPos.y -= 2;			/* Try to move barrier up */
			break;
		case MOV_DOWN:
			newPos.y += 2;			/* Try to move barrier down */
			break;
		case MOV_RIGHT:
			newPos.x += 2;			/* Try to move barrier right */
			break;
		case MOV_LEFT:
			newPos.x -= 2;			/* Try to move barrier left */
			break;
	}
	if (isValidBarrierSquare(newPos, barrier.direction)) {	/* Barrier can be placed */
		deleteBarrier(barrier);							/* Hide current barrier 			*/
		barrier.centrePos.x = newPos.x;			/* Update barrier coordinates */
		barrier.centrePos.y = newPos.y;
		drawAllBarriers(barriers, placedBarriers);		/* Render all the placed barriers */
		drawBarrier(barrier);								/* Draw moved barrier 				*/
	}
}

void rotateBarrier() {
	/* Delete current barrier and change direction */
	deleteBarrier(barrier);			
	barrier.direction = barrier.direction == HORIZONTAL ? VERTICAL : HORIZONTAL;
	drawAllBarriers(barriers, placedBarriers);		/* Render all the placed barriers */
	drawBarrier(barrier);
}

void placeBarrier() {
	/* Check whether barrier can't be placed because of other barriers */
	if (isBarrierOverlapping(barrier.centrePos, barrier.direction)) 
		return;
	barrier.color = BARRIER_COLOR;				// TODO: color can be changed according to current player
	barriers[placedBarriers++] = barrier;		/* Add barrier to placed barriers list */
	updateBoardBarrier(barrier.centrePos, barrier.direction);	/* Update board values */
	drawBarrier(barrier);			/* Render barrier with normal color */
	game.status = MOVING;
	startNewTurn();
}



