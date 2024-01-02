#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h"

typedef enum game_status {
    WAITING,
    STARTED,
    FINISHED
} GameStatus;

typedef enum movement {
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
} Movement;

void initGame(void);

#endif
