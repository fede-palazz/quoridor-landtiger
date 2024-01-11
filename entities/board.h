#ifndef BOARD_H
#define BOARD_H

#include "../game/constants.h"
#include "../utils/datatypes.h"
#include "barrier.h"
#include "player.h"


extern void initBoard(Coordinate p1Pos, Coordinate p2Pos);
extern uint8_t isValidSquare(Coordinate squarePos);
extern uint8_t isEmptySquare(Coordinate squarePos);
extern uint8_t isPlayerSquare(Coordinate squarePos);
extern uint8_t isBarrierSquare(Coordinate squarePos);
extern void updateBoardPlayer(Player* player);
extern uint8_t isValidBarrierSquare(Coordinate centrePos, Direction direction);
extern void insertBoardBarrier(Coordinate centrePos, Direction direction);
extern uint8_t isBarrierOverlapping(Coordinate centrePos, Direction direction);
extern uint8_t isBarrierBlockingPlayer(Barrier barrier, Coordinate playerPos, uint8_t currentTurn);

#endif
