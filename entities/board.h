#ifndef BOARD_H
#define BOARD_H

#include "../game/constants.h"
#include "../utils/datatypes.h"
#include "player.h"


//extern volatile uint8_t board[BOARD_SIZE][BOARD_SIZE];

extern void initBoard(Coordinate p1Pos, Coordinate p2Pos);
extern uint8_t isValidSquare(Coordinate squarePos);
extern uint8_t isEmptySquare(Coordinate squarePos);
extern uint8_t isPlayerSquare(Coordinate squarePos);
extern uint8_t isBarrierSquare(Coordinate squarePos);
extern void updateBoardPlayer(Player* player);

#endif
