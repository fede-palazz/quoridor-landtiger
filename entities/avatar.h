#ifndef AVATAR_H
#define AVATAR_H

#include "../game/constants.h"

#define AVATAR_SIZE					26
#define NUM_AVATARS 				8


typedef struct Avatar {
	uint8_t (*pixelData)[AVATAR_SIZE];
	int16_t color;
} Avatar;

extern Avatar get_random_avatar(Color color);

#endif
