#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h"

typedef enum game_status {
    WAITING,
    STARTED,
    FINISHED
} GameStatus;

typedef struct game {
	GameStatus status;
	uint8_t turn;
	uint8_t countdown;
} Game;

typedef enum movement {
	MOV_UP,
	MOV_DOWN,
	MOV_LEFT,
	MOV_RIGHT
} Movement;

extern volatile Game game;


extern void initGame(void);
extern void highlightSquares(void);

#endif
