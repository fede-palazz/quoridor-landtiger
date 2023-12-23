#include "renderer.h"


void drawRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor) {
	if (outlineColor) {
	// Draw outlines
	LCD_DrawLine(p1.x, p1.y, p2.x, p1.y, outlineColor);
	LCD_DrawLine(p1.x, p1.y, p1.x, p2.y, outlineColor);
	LCD_DrawLine(p2.x, p1.y, p2.x, p2.y, outlineColor);
	LCD_DrawLine(p1.x, p2.y, p2.x, p2.y, outlineColor);
	}
	if (fillColor) {
		int lineNum = p1.y + 1;
		while (lineNum != p2.y) {
			LCD_DrawLine(p1.x + 1, lineNum, p2.x - 1, lineNum, fillColor);
			lineNum += 1;
		}
	}
}
