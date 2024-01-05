#include "player.h"


void initPlayer(Player* player, Coordinate pos, Color color) {
	player->avatar = get_random_avatar(color);
	player->pos = pos;
	player->previousPos = pos;
}

void setPlayerPos(Player* player, uint16_t x, uint16_t y) {
	/* Set current position as previous position*/
	player->previousPos.x = player->pos.x;
	player->previousPos.y = player->pos.y;
	/* Update new position */
	player->pos.x = x;
	player->pos.y = y;
}
