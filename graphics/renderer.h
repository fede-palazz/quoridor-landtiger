#ifndef RENDERER_H
#define RENDERER_H

#include "LPC17xx.h"
#include "../TouchPanel/TouchPanel.h"
#include "../GLCD/GLCD.h" 

#define Color uint16_t

extern void drawRectangle(Coordinate p1, Coordinate p2, Color outlineColor, Color fillColor);

#endif
