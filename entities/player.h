#ifndef PLAYER_H
#define PLAYER_H

#include "../game/constants.h"
#include "../utils/datatypes.h"
#include "avatar.h"


typedef struct Player {
	Avatar avatar;
	Coordinate pos;
} Player;

extern void initPlayer(Player* player, Coordinate pos, Color color);
extern void setPlayerPos(Player* player, uint16_t x, uint16_t y);


#endif
