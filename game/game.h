#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h"
#include "../utils/input.h"

typedef enum game_status {
    WAITING,
    MOVING,
		PLACING,
    FINISHED
} GameStatus;

typedef struct game {
	GameStatus status;
	uint8_t turn;
	uint8_t countdown;
} Game;

typedef enum movement {
	MOV_LEFT,
	MOV_UP,
	MOV_DOWN,
	MOV_RIGHT
} Movement;

extern volatile Game game;
extern Player* currentPlayer;
extern volatile int8_t selectedSquare;
extern volatile Coordinate possibleMoves[];
extern volatile uint8_t board[BOARD_SIZE][BOARD_SIZE];

extern void initGame(void);
extern void highlightSquares(void);
extern void clearHighlightedSquares(void);
extern void selectSquare(Movement movement);
extern void startNewTurn(void);
extern void movePlayer(void);

#endif
