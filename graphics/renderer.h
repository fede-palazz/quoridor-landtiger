#ifndef RENDERER_H
#define RENDERER_H

#include "../GLCD/GLCD.h" 
#include "../game/constants.h"
#include "../entities/avatar.h"


extern void drawRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor);
extern void drawThickRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor, uint16_t thicknessPx);
extern void drawAvatar(Avatar avatar, Coordinate squarePos);

#endif
