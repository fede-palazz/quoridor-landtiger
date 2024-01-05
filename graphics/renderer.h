#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include "../GLCD/GLCD.h" 
#include "../game/constants.h"
#include "../utils/datatypes.h"
#include "../entities/avatar.h"
#include "../entities/player.h"
#include "../entities/board.h"


extern void drawRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor);
extern void drawThickRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor, uint16_t thicknessPx);
extern void fillSquare(Coordinate squarePos, Color color);
extern void drawAvatar(Avatar avatar, Coordinate squarePos);
extern void drawBoard(Color outlineColor, Color fillColor);
extern void drawPlayers(Player* p1, Player* p2);
extern void drawNewPlayerPos(Player* p);
extern void drawInitialLabels(void);
extern void drawInitialMessage(void);
extern void hideInitialMessage(void);

#endif
