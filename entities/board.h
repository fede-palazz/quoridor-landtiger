#ifndef BOARD_H
#define BOARD_H

#include "../game/constants.h"
#include "../utils/datatypes.h"
#include "avatar.h"


extern volatile uint8_t board[BOARD_SIZE][BOARD_SIZE];

extern uint8_t isValidSquare(Coordinate squarePos);
extern uint8_t isEmptySquare(Coordinate squarePos);
extern uint8_t isPlayerSquare(Coordinate squarePos);
extern uint8_t isBarrierSquare(Coordinate squarePos);

#endif
