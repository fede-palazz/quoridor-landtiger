#include "renderer.h"

/*
*	Return base 7 LCD coordinates of a square without borders
*/
Coordinate getSquarePositionLCD(Coordinate squarePos) {
	Coordinate pos;
	// Convert base 13 coordinates into base 7
	squarePos.x /= 2;
	squarePos.y /= 2;
	// Calculate initial position on screen
	pos.x = LAT_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.x + SQUARE_BORDERS;
	pos.y = TOP_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.y + SQUARE_BORDERS;
	return pos;
}

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
	Coordinate startPos = getSquarePositionLCD(squarePos);
	Coordinate endPos;
	endPos.x = startPos.x + SQUARE_LENGTH - SQUARE_BORDERS*2;
	endPos.y = startPos.y + SQUARE_LENGTH - SQUARE_BORDERS*2;
	drawRectangle(startPos, endPos, color, color);
}
	
void drawAvatar(Avatar avatar, Coordinate squarePos) {
	int row, col;
	Coordinate pos = getSquarePositionLCD(squarePos);
	// Draw avatar
	for (row=0; row<AVATAR_SIZE; row++)
		for (col=0; col<AVATAR_SIZE; col++)
			// If pixel should be coloured
			if (avatar.pixelData[row][col])
				LCD_SetPoint(pos.x + col, pos.y + row, avatar.color);
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

void drawPlayers(Player* p1, Player* p2) {
	drawAvatar(p1->avatar, p1->pos);
	drawAvatar(p2->avatar, p2->pos);
}

void drawNewPlayerPos(Player* p) {
	/* Hide avatar in current player position */
	fillSquare(p->previousPos, SQUARE_COLOR);
	/* Draw avatar in new position */
	drawAvatar(p->avatar, p->pos);
}

void drawInitialLabels() {
	// Players' barriers
	GUI_Text(LAT_PADDING + 5, LAT_PADDING + 3, (uint8_t *) "P1 walls: 8", TXT_COLOR, BG_COLOR); 
	GUI_Text(LAT_PADDING + 132, LAT_PADDING + 3, (uint8_t *) "P2 walls: 8", TXT_COLOR, BG_COLOR); 
}

void drawInitialMessage() {
	// Bottom message
	GUI_Text(LAT_PADDING + 2, LCD_HEIGHT - 30, (uint8_t *) "Press INT0 to start the game", TXT_COLOR, BG_COLOR); 
}

void hideInitialMessage() {
	// TODO: substitute WHITE with BG_COLOR
	GUI_Text(LAT_PADDING + 2, LCD_HEIGHT - 30, (uint8_t *) "Press INT0 to start the game", WHITE, BG_COLOR); 
}
