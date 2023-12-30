#include "player.h"


void initPlayer(Player* player, Coordinate pos, Color color) {
	player->avatar = get_random_avatar(color);
	player->pos = pos;
}

void setPlayerPos(Player* player, uint16_t x, uint16_t y) {
	player->pos.x = x;
	player->pos.y = y;
}
