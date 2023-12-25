#ifndef RENDERER_H
#define RENDERER_H

#include "LPC17xx.h"
//#include "../TouchPanel/TouchPanel.h"
#include "../GLCD/GLCD.h" 
#include "colors.h"


typedef struct POINT 
{
   uint16_t x;
   uint16_t y;
} Coordinate;

extern void drawRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor);
extern void drawThickRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor, uint16_t thicknessPx);

#endif
