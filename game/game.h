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
	uint32_t lastMove;
} Game;

typedef enum movement {
	MOV_LEFT,
	MOV_UP,
	MOV_DOWN,
	MOV_RIGHT
} Movement;

extern volatile Game game;
extern Player* currentPlayer;
extern volatile Barrier barrier;
extern int8_t selectedSquare;
extern volatile Coordinate possibleMoves[];
extern volatile uint8_t board[BOARD_SIZE][BOARD_SIZE];
extern volatile uint8_t isBarrierWarningDisplayed;

extern void initGame(void);
extern void highlightSquares(void);
extern void clearHighlightedSquares(void);
extern void selectSquare(Movement movement);
extern void startNewTurn(void);
extern void movePlayer(void);
extern void createNewBarrier(void);
extern void moveBarrier(Movement movement);
extern void rotateBarrier(void);
extern uint8_t placeBarrier(void);
extern void switchToMovingMode(void);
extern uint8_t checkWinningCondition(void);
extern void resetGame(void);
extern void saveLastMove(uint8_t playerId, uint8_t isPlacingBarrier, uint8_t isBarrierHorizontal, uint8_t posY, uint8_t posX);

#endif
