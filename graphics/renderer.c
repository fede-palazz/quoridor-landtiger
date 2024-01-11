#include "renderer.h"

/********************
* COORDINATES UTILS *
*********************/

/*
*	Return base 7 LCD coordinates of a square without borders
*/
Coordinate getSquarePositionLCD(Coordinate squarePos, uint8_t excludeBorders) {
	Coordinate pos;
	// Convert base 13 coordinates into base 7
	squarePos.x /= 2;
	squarePos.y /= 2;
	// Calculate initial position on screen
	if (excludeBorders) {
		pos.x = LAT_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.x + SQUARE_BORDERS;
		pos.y = TOP_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.y + SQUARE_BORDERS;
	}
	else {
		pos.x = LAT_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.x;
		pos.y = TOP_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.y;
	}
	return pos;
}

Coordinate getBarrierPositionLCD(Coordinate barrierPos, Direction direction) {
	// Get screen coordinates of the top left square
	Coordinate pos = getSquarePositionLCD(barrierPos, 0);
	// Check barrier direction
	if (direction == HORIZONTAL)
		pos.y += SQUARE_LENGTH + 1;
	else
		pos.x += SQUARE_LENGTH + 1;
	return pos;
}

/*******************
* GEOMETRIC SHAPES *
********************/

void drawRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor) {
	int lineNum;

	if (outlineColor != NO_COLOR) {
		// Draw outlines
		LCD_DrawLine(p1.x, p1.y, p2.x, p1.y, outlineColor);
		LCD_DrawLine(p1.x, p1.y, p1.x, p2.y, outlineColor);
		LCD_DrawLine(p2.x, p1.y, p2.x, p2.y, outlineColor);
		LCD_DrawLine(p1.x, p2.y, p2.x, p2.y, outlineColor);
	}
	if (fillColor != NO_COLOR) {
		// Fill shape
		lineNum	= p1.y + 1;
		while (lineNum != p2.y) {
			LCD_DrawLine(p1.x + 1, lineNum, p2.x - 1, lineNum, fillColor);
			lineNum++;
		}
	}
}

void drawThickRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor, uint16_t thicknessPx) {
	int i = 0;
	// Draw thick border
	while (i < thicknessPx - 1) {
		drawRectangle(p1, p2, outlineColor, NO_COLOR);
		p1.x++;
		p1.y++;
		p2.x--;
		p2.y--;
		i++;
	}
	// Fill the rectangle
	drawRectangle(p1, p2, outlineColor, fillColor);
}

void fillSquare(Coordinate squarePos, Color color) {
	Coordinate startPos = getSquarePositionLCD(squarePos, 1);
	Coordinate endPos;
	endPos.x = startPos.x + SQUARE_LENGTH - SQUARE_BORDERS*2;
	endPos.y = startPos.y + SQUARE_LENGTH - SQUARE_BORDERS*2;
	drawRectangle(startPos, endPos, color, color);
}

/***************************
* GAME RENDERING FUNCTIONS *
****************************/

void drawAvatar(Avatar avatar, Coordinate squarePos) {
	int row, col;
	Coordinate pos = getSquarePositionLCD(squarePos, 1);
	// Draw avatar
	for (row=0; row<AVATAR_SIZE; row++)
		for (col=0; col<AVATAR_SIZE; col++)
			// If pixel should be coloureds
			if (avatar.pixelData[row][col])
				LCD_SetPoint(pos.x + col, pos.y + row, avatar.color);
}

void deleteAvatar(Avatar avatar, Coordinate squarePos, Color squareColor) {
	int row, col;
	Coordinate pos = getSquarePositionLCD(squarePos, 1);
	// Hide avatar
	for (row=0; row<AVATAR_SIZE; row++)
		for (col=0; col<AVATAR_SIZE; col++)
			// If pixel belongs to avatar
			if (avatar.pixelData[row][col])
				LCD_SetPoint(pos.x + col, pos.y + row, squareColor);
}

void drawPlayers(Player* p1, Player* p2) {
	drawAvatar(p1->avatar, p1->pos);
	drawAvatar(p2->avatar, p2->pos);
}

void drawNewPlayerPos(Player* p, Color squareColor) {
	/* Hide avatar in current player position */
	deleteAvatar(p->avatar, p->previousPos, squareColor);
	//fillSquare(p->previousPos, SQUARE_COLOR);
	/* Draw avatar in new position */
	drawAvatar(p->avatar, p->pos);
}

void drawBoard(Color outlineColor, Color fillColor) {
	int row, col;
	Coordinate p1, p2;

	for (row=0; row<SQUARE_NUM; row++) {
		// Update coordinates for next row
		p1.x = LAT_PADDING;
		p1.y = TOP_PADDING + (SQUARE_LENGTH + INT_PADDING) * row;
		p2.x = LAT_PADDING + SQUARE_LENGTH;
		p2.y = TOP_PADDING + (SQUARE_LENGTH + INT_PADDING) * row + SQUARE_LENGTH;
		
		for (col=0; col<SQUARE_NUM; col++) {
			drawThickRectangle(p1, p2, outlineColor, fillColor, SQUARE_BORDERS);
			// Update coordinates for next col
			p1.x += SQUARE_LENGTH + INT_PADDING;
			p2.x += SQUARE_LENGTH + INT_PADDING;
		}
	}
}

void drawBarrier(Barrier barrier) {
	int i;
	Coordinate startPos = getBarrierPositionLCD(barrier.centrePos, barrier.direction);
	if (barrier.direction == HORIZONTAL) {
		for (i=0; i<INT_PADDING-1; i++)
			LCD_DrawLine(startPos.x - 1, startPos.y + i, startPos.x + INT_PADDING + SQUARE_LENGTH*2 + 1, startPos.y + i, barrier.color);
	}
	else {
		for (i=0; i<INT_PADDING-1; i++)
			LCD_DrawLine(startPos.x + i, startPos.y - 1, startPos.x + i, startPos.y + INT_PADDING + SQUARE_LENGTH*2 + 1, barrier.color);
	}
}

void drawAllBarriers(Barrier* barriers, uint8_t barriersTot) {
	int i;
	for (i=0; i<barriersTot; i++)
		drawBarrier(barriers[i]);
}

void deleteBarrier(Barrier barrier) {
	barrier.color = BARRIER_BG_COLOR;
	drawBarrier(barrier);
}

void deleteAllBarriers(Barrier* barriers, uint8_t barriersTot) {
	int i;
	for (i=0; i<barriersTot; i++) {
		deleteBarrier(barriers[i]);
	}
}

/***********************
*	USER MESSAGES / INFO *
************************/

void drawInitialLabels() {
	// Players' barriers
	GUI_Text(LAT_PADDING + 5, LAT_PADDING + 3, (uint8_t *) "P1 walls: ", TXT_COLOR, BG_COLOR); 
	refreshBarrierNum(BARRIER_NUM, 1);
	GUI_Text(LAT_PADDING + 132, LAT_PADDING + 3, (uint8_t *) "P2 walls: ", TXT_COLOR, BG_COLOR); 
	refreshBarrierNum(BARRIER_NUM, 2);
}

void drawInitialMessage() {
	// Bottom message
	GUI_Text(LAT_PADDING + 2, LCD_HEIGHT - 38, (uint8_t *) "Press INT0 to start the game", TXT_COLOR, BG_COLOR); 
}

void drawCurrentTurnMessage(Player* player, uint8_t currentTurn) {
	// TODO: draw small avatar
	if (currentTurn == 1)
			GUI_Text(LAT_PADDING + 2, LCD_HEIGHT - 38, (uint8_t *) "     P1 it's your turn!     ", TXT_COLOR, BG_COLOR);
	else
			GUI_Text(LAT_PADDING + 2, LCD_HEIGHT - 38, (uint8_t *) "     P2 it's your turn!     ", TXT_COLOR, BG_COLOR);
}

void updateCurrentTurnMessage(Player* player, uint8_t currentTurn) {
	// TODO: draw small avatar
	if (currentTurn == 1)
		GUI_Text(LAT_PADDING + 50, LCD_HEIGHT - 38, (uint8_t *) "1", TXT_COLOR, BG_COLOR);
	else
		GUI_Text(LAT_PADDING + 50, LCD_HEIGHT - 38, (uint8_t *) "2", TXT_COLOR, BG_COLOR);
}

void drawNoBarriersMessage() {
	// max 30 chars in a row
	GUI_Text(LAT_PADDING, 302, (uint8_t *) "no more walls, move the token", TXT_COLOR_2, BG_COLOR);
}

void drawTrapMessage() {
	GUI_Text(LAT_PADDING, 302, (uint8_t *) "  you can't trap a player!   ", TXT_COLOR_2, BG_COLOR);
}

void hideSecondaryMessage() {
	GUI_Text(LAT_PADDING, 302, (uint8_t *) "                             ", BG_COLOR, BG_COLOR);
}

void refreshBarrierNum(uint8_t barrierNum, uint8_t currentTurn) {
	uint8_t buffer[2];	/* Temporary char array */
	sprintf((char *)buffer, "%d", barrierNum); /* Convert barrierNum value into char array */
	if (currentTurn == 1)
		GUI_Text(LAT_PADDING + 85, LAT_PADDING + 3, buffer, TXT_COLOR, BG_COLOR); 
	else
		GUI_Text(LAT_PADDING + 212, LAT_PADDING + 3, buffer, TXT_COLOR, BG_COLOR); 
}

void drawWinningMessage() {
	GUI_Text(LAT_PADDING + 66, LCD_HEIGHT - 38, (uint8_t *) "won the game!  ", TXT_COLOR, BG_COLOR);
	GUI_Text(LAT_PADDING, 302, (uint8_t *) "Press INT0 to restart the game", TXT_COLOR_2, BG_COLOR);
}
