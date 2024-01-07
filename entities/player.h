#ifndef PLAYER_H
#define PLAYER_H

#include "../game/constants.h"
#include "../utils/datatypes.h"
#include "avatar.h"


typedef struct Player {
	Avatar avatar;
	Coordinate pos;
	Coordinate previousPos;
	uint8_t barrierNum;
} Player;

extern void initPlayer(Player* player, Coordinate pos, Color color, uint8_t barrierNum);
extern void setPlayerPos(Player* player, uint16_t x, uint16_t y);


#endif
