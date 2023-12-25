#include "game.h"


int getSquaresLength(uint8_t externalPadding, uint8_t internalPadding);



void drawBoard(Color outlineColor, Color fillColor, uint16_t borders) {
	int squareLen = getSquaresLength(LAT_PADDING, INT_PADDING);
	int row, col;
	Coordinate p1, p2;

	for (row=0; row<SQUARE_NUM; row++) {
		// Update coordinates for next row
		p1.x = LAT_PADDING;
		p1.y = TOP_PADDING + (squareLen + INT_PADDING) * row;
		p2.x = LAT_PADDING + squareLen;
		p2.y = TOP_PADDING + (squareLen + INT_PADDING) * row + squareLen;
		
		for (col=0; col<SQUARE_NUM; col++) {
			drawThickRectangle(p1, p2, outlineColor, fillColor, borders);
			// Update coordinates for next col
			p1.x += squareLen + INT_PADDING;
			p2.x += squareLen + INT_PADDING;
		}
	}
}

int getSquaresLength(uint8_t externalPadding, uint8_t internalPadding) {
	return (LCD_WIDTH - externalPadding * 2 - (internalPadding * (SQUARE_NUM - 1))) / SQUARE_NUM;
//	int expression = LCD_WIDTH - externalPadding * 2 - (internalPadding * (SQUARE_NUM - 1));
//	int result = expression / SQUARE_NUM;
//	int remainder = expression % SQUARE_NUM;
//	// Round result if necessary
//	return remainder * 2 > SQUARE_NUM ? result+1 : result;
}
