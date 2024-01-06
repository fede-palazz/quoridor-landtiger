#ifndef BARRIER_H
#define BARRIER_H

#include "../game/constants.h"
#include "../utils/datatypes.h"

typedef enum direction {
	VERTICAL,
	HORIZONTAL
} Direction;

typedef struct barrier {
	Color color;
	Coordinate centrePos;
	Direction direction;
} Barrier;


#endif
