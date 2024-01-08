#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include "../GLCD/GLCD.h" 
#include "../game/constants.h"
#include "../entities/board.h"
#include "../entities/player.h"
#include "../utils/datatypes.h"
#include "../entities/barrier.h"


extern void drawRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor);
extern void drawThickRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor, uint16_t thicknessPx);
extern void fillSquare(Coordinate squarePos, Color color);
extern void drawAvatar(Avatar avatar, Coordinate squarePos);
extern void drawBoard(Color outlineColor, Color fillColor);
extern void drawPlayers(Player* p1, Player* p2);
extern void drawNewPlayerPos(Player* p);
extern void drawInitialLabels(void);
extern void drawInitialMessage(void);
extern void drawCurrentTurn(Player* player, uint8_t currentTurn);
extern void updateCurrentTurn(Player* player, uint8_t currentTurn);
extern void drawBarrier(Barrier barrier);
extern void deleteBarrier(Barrier barrier);
extern void drawNoBarriersMessage(void);
extern void hideNoBarriersMessage(void);
extern void drawAllBarriers(Barrier* barriers, uint8_t barriersTot);
extern void refreshBarrierNum(uint8_t barrierNum, uint8_t currentTurn);

#endif
