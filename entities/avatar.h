#ifndef AVATAR_H
#define AVATAR_H

#include "../game/constants.h"

#define AVATAR_SIZE		26
#define NUM_AVATARS 	2


typedef struct Avatar {
	uint8_t (*pixelData)[AVATAR_SIZE];
	int16_t color;
} Avatar;

static uint8_t avatar_1_pixel_data[AVATAR_SIZE][AVATAR_SIZE];
static uint8_t avatar_2_pixel_data[AVATAR_SIZE][AVATAR_SIZE];

extern Avatar get_random_avatar(Color color);

#endif
