#include "renderer.h"


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
			lineNum += 1;
		}
	}
}

void drawThickRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor, uint16_t thicknessPx) {
	
	int i = 0;
	// draw thick border
	while (i < thicknessPx - 1) {
		drawRectangle(p1, p2, outlineColor, NO_COLOR);
		p1.x += 1;
		p1.y += 1;
		p2.x -= 1;
		p2.y -= 1;
		i += 1;
	}
	// fill the rectangle
	drawRectangle(p1, p2, outlineColor, fillColor);
}
	
void drawAvatar(Avatar avatar, Coordinate squarePos) {
	int row, col;
	Coordinate pos;
	
	// Calculate initial position on screen
	pos.x = LAT_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.x + SQUARE_BORDERS;
	pos.y = TOP_PADDING + (INT_PADDING + SQUARE_LENGTH)*squarePos.y + SQUARE_BORDERS;

	// Draw avatar
	for (row=0; row<AVATAR_SIZE; row++) {
		for (col=0; col<AVATAR_SIZE; col++) {
			// if pixel should be coloured
			if (avatar.pixelData[row][col]) {
				LCD_SetPoint(pos.x + col, pos.y + row, avatar.color);
			}
		}
	}
}
